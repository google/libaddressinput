# Copyright (C) 2013 Google Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
{
  'variables': {
    'component%': 'shared_library',
  },
  'target_defaults': {
    'conditions': [
      ['OS == "linux" and "<(component)" == "shared_library"', {
        # https://code.google.com/p/gyp/issues/detail?id=374
        'cflags': ['-fPIC'],
      }],
    ],
    'include_dirs': [
      'include',
    ],
  },
  'targets': [
    {
      'target_name': 'libaddressinput',
      'type': '<(component)',
      'sources': [
        'src/region_data_constants.cc',
        'src/util/json.cc',
      ],
      'dependencies': [
        'grit.gyp:generated_messages',
        'rapidjson.gyp:rapidjson',
      ],
    },
    {
      'target_name': 'unit_tests',
      'type': 'executable',
      'sources': [
        'test/region_data_constants_test.cc',
        'test/util/json_test.cc',
      ],
      'include_dirs': [
        'src',
      ],
      'dependencies': [
        'libaddressinput',
        'gtest.gyp:main',
      ],
      'conditions': [
        [ 'OS == "mac"', {
          'postbuilds': [
            {
              # To make it possible to execute the unit tests directly from the
              # build directory, without first installing the library, the path
              # to the library is set to be relative to the unit test executable
              # (so that also the library will be loaded directly from the build
              # directory).
              'postbuild_name': 'Make dylib path relative to executable',
              'action': [
                'install_name_tool',
                '-change',
                '/usr/local/lib/libaddressinput.dylib',
                '@executable_path/libaddressinput.dylib',
                '${BUILT_PRODUCTS_DIR}/${EXECUTABLE_PATH}'
              ],
            },
          ],
        }],
      ],
    },
  ],
}
