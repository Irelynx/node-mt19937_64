{
  'targets': [
    {
      'target_name': 'mt19937_64',
      'sources': [
        'src/bindings.cc'
      ],
      'libraries': [],
      'cflags': [
        '-O2',
        '-Wall',
        '-Wextra',
        '-std=c++11'
      ]
    }
  ]
}