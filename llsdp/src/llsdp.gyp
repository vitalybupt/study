{
  'targets': [
    {
      'target_name': 'llsdp',
      'type': 'static_library',
      'include_dirs': [ '.', 'include' ],
      'direct_dependent_settings': {
        'include_dirs': [ 'include' ],
      },
      'sources': [ 'src/llsdp.c', 'src/api.c', 'src/sdp.c' ],
    },
  ]
}
