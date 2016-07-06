{
    'targets': [
        {
            'target_name': 'osIdleTimer',
            'sources': [
                './src/module.cc',
                './src/win/idleTime.c'
            ],

            'include_dirs': [
                './src/idleTime.h'
            ],

            'conditions': [
                ['OS == "win"', {
                    'libraries': [],
                    'configurations' : {
                        'Debug' : {
                            'msvs_settings': {
                                'VCCLCompilerTool': {
                                    'RuntimeLibrary': '3' # /MDd
                                },
                                'VCLinkerTool': {
                                    'AdditionalOptions': ['/ignore:4099'],
                                    'IgnoreDefaultLibraryNames': ['libcmtd.lib']
                                }
                            }
                        },
                        'Release' : {
                            'msvs_settings': {
                                'VCCLCompilerTool': {
                                    'RuntimeTypeInfo': 'true', # To disable '/GR-'
                                    'RuntimeLibrary': '2' # /MDd
                                },
                                'VCLinkerTool': {
                                    'AdditionalOptions': ['/ignore:4099'],
                                    'IgnoreDefaultLibraryNames': ['libcmt.lib']
                                }
                            }
                        }
                    }
                }],
                ['OS == "darwin"', {
                    'xcode_settings': {
                        'GCC_ENABLE_CPP_RTTI': 'YES',
                        "OTHER_CFLAGS": [ "-D__MAC_OS__ -DOSX" ]
                    },
                    'libraries': []
                }]
            ]
        }
    ]
}
