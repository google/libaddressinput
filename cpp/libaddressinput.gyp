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
        'src/address_field.cc',
        'src/address_field_util.cc',
        'src/address_ui.cc',
        'src/localization.cc',
        'src/lookup_key_util.cc',
        'src/region_data_constants.cc',
        'src/retriever.cc',
        'src/rule.cc',
        'src/rule_retriever.cc',
        'src/util/json.cc',
        'src/util/md5.cc',
        'src/validating_storage.cc',
        'src/validating_util.cc',
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
        'test/address_field_util_test.cc',
        'test/address_ui_test.cc',
        'test/fake_downloader.cc',
        'test/fake_downloader_test.cc',
        'test/fake_storage.cc',
        'test/fake_storage_test.cc',
        'test/localization_test.cc',
        'test/lookup_key_util_test.cc',
        'test/region_data_constants_test.cc',
        'test/retriever_test.cc',
        'test/rule_retriever_test.cc',
        'test/rule_test.cc',
        'test/util/json_test.cc',
        'test/util/md5_unittest.cc',
        'test/util/scoped_ptr_unittest.cc',
        'test/validating_storage_test.cc',
        'test/validating_util_test.cc',
      ],
      'defines': [
        'TEST_DATA_DIR="../testdata"',
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
