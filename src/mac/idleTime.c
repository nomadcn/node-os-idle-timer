/*****************************************
  * idler.c
  *
  * Uses IOKit to figure out the idle time of the system. The idle time
  * is stored as a property of the IOHIDSystem class; the name is
  * HIDIdleTime. Stored as a 64-bit int, measured in ns.
  *
  * The program itself just prints to stdout the time that the computer has
  * been idle in seconds.
  *
  * Compile with gcc -Wall -framework IOKit -framework Carbon idler.c -o
  * idler
  *
  * Copyright (c) 2003, Stanford University
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted provided that the following conditions are
  * met:
  * Redistributions of source code must retain the above copyright notice,
  * this list of conditions and the following disclaimer.
  *
  * Redistributions in binary form must reproduce the above copyright notice,
  * this list of conditions and the following disclaimer in the documentation
  * and/or other materials provided with the distribution.
  *
  * Neither the name of Stanford University nor the names of its contributors
  * may be used to endorse or promote products derived from this software
  * without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
  * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
  * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
  * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
  * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
  * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
  * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
  * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  */

#include <CoreFoundation/CoreFoundation.h>
#include <CoreServices/CoreServices.h>
#include <IOKit/IOKitLib.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int64_t getIdleTime_ms()
{
    int64_t idleTime_ms = -1;
    mach_port_t masterPort;
    io_iterator_t iter;
    io_registry_entry_t curObj;

    IOMasterPort(MACH_PORT_NULL, &masterPort);

    /* Get IOHIDSystem */
    IOServiceGetMatchingServices(
        masterPort, IOServiceMatching("IOHIDSystem"), &iter);
    if (iter)
    {
        printf("Error accessing IOHIDSystem\n");
        return -1;
    }

    curObj = IOIteratorNext(iter);
    if (curObj == NULL)
    {
        printf("Iterator's empty!\n");
        IOObjectRelease(iter);
        return -2;
    }

    CFMutableDictionaryRef properties = NULL;
    CFTypeRef obj;

    if (IORegistryEntryCreateCFProperties(
            curObj, &properties, kCFAllocatorDefault, 0) ==
            KERN_SUCCESS && properties != NULL)
    {
        obj = CFDictionaryGetValue(properties, CFSTR("HIDIdleTime"));
        CFRetain(obj);
    }
    else
    {
        printf("Couldn't grab properties of system\n");
        obj = NULL;
    }

    if (obj)
    {
        idleTime_ms = getIdleTime_ms(obj);
        CFRelease(obj);
    }

    // Release resources
    CFRelease((CFTypeRef)properties);
    IOObjectRelease(curObj);
    IOObjectRelease(iter);

    return idleTime_ms;
}

int64_t getIdleTime_ms(CFTypeRef obj)
{
    int ret = 0;

    if (obj == NULL)
    {
        return -1;
    }

    uint64_t tHandle;
    CFTypeID type = CFGetTypeID(obj);

    if (type == CFDataGetTypeID())
    {
        CFDataGetBytes(
            (CFDataRef) obj,
            CFRangeMake(0, sizeof(tHandle)), (UInt8*) &tHandle);
    }
    else if (type == CFNumberGetTypeID())
    {
        CFNumberGetValue((CFNumberRef)obj, kCFNumberSInt64Type, &tHandle);
    }
    else
    {
        return -2;
    }

    // unit conversion: ns(10^-9s) -> ms(10^-3s)
    return (int64_t) (tHandle / 1000000LL);
}
