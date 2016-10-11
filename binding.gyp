{
    'targets': [
        {
            'target_name': '<(module_name)',
            'include_dirs': [
                './src'
            ],
            'sources': [
                './src/module.cc'
            ],

            'conditions': [
                ['OS == "win"', {
                    'sources': [
                        './src/win/idleTime.c'
                    ],

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
                ['OS == "mac"', {
                    'sources': [
                        './src/mac/idleTime.c'
                    ],
                    'xcode_settings': {
                        "OTHER_CFLAGS": [
                            "-D__MAC_OS__",
                            "-DOSX",
                            "-Wall"
                        ],
                        "OTHER_LDFLAGS": [
                            "-framework IOKit",
                            "-framework Carbon"
                        ]
                    },
                }]
            ]
        },
        {
            "target_name": "action_after_build",
            "type": "none",
            "dependencies": [ "<(module_name)" ],
            "copies": [
                {
                    "files": [ "<(PRODUCT_DIR)/<(module_name).node" ],
                    "destination": "<(module_path)"
                }
            ]
        }
    ]
}
