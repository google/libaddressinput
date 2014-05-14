# Copyright (C) 2014 Google Inc.
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
    'variables': {
      'libaddressinput_dir%': '.',
    },
    'libaddressinput_sources': [
      '<(libaddressinput_dir)/src/address_data.cc',
      '<(libaddressinput_dir)/src/address_field.cc',
      '<(libaddressinput_dir)/src/address_field_util.cc',
      '<(libaddressinput_dir)/src/address_problem.cc',
      '<(libaddressinput_dir)/src/address_ui.cc',
      '<(libaddressinput_dir)/src/address_validator.cc',
      '<(libaddressinput_dir)/src/language.cc',
      '<(libaddressinput_dir)/src/localization.cc',
      '<(libaddressinput_dir)/src/lookup_key.cc',
      '<(libaddressinput_dir)/src/lookup_key_util.cc',
      '<(libaddressinput_dir)/src/metadata_loader.cc',
      '<(libaddressinput_dir)/src/metadata_query_task.cc',
      '<(libaddressinput_dir)/src/null_storage.cc',
      '<(libaddressinput_dir)/src/post_box_matchers.cc',
      '<(libaddressinput_dir)/src/region_data_constants.cc',
      '<(libaddressinput_dir)/src/retriever.cc',
      '<(libaddressinput_dir)/src/rule.cc',
      '<(libaddressinput_dir)/src/rule_retriever.cc',
      '<(libaddressinput_dir)/src/util/json.cc',
      '<(libaddressinput_dir)/src/util/md5.cc',
      '<(libaddressinput_dir)/src/util/string_split.cc',
      '<(libaddressinput_dir)/src/validating_storage.cc',
      '<(libaddressinput_dir)/src/validating_util.cc',
      '<(libaddressinput_dir)/src/validation_task.cc',
    ],
    'libaddressinput_test_sources': [
      '<(libaddressinput_dir)/test/address_data_test.cc',
      '<(libaddressinput_dir)/test/address_field_test.cc',
      '<(libaddressinput_dir)/test/address_field_util_test.cc',
      '<(libaddressinput_dir)/test/address_problem_test.cc',
      '<(libaddressinput_dir)/test/address_ui_test.cc',
      '<(libaddressinput_dir)/test/address_validator_test.cc',
      '<(libaddressinput_dir)/test/fake_downloader.cc',
      '<(libaddressinput_dir)/test/fake_downloader_test.cc',
      '<(libaddressinput_dir)/test/fake_storage.cc',
      '<(libaddressinput_dir)/test/fake_storage_test.cc',
      '<(libaddressinput_dir)/test/language_test.cc',
      '<(libaddressinput_dir)/test/localization_test.cc',
      '<(libaddressinput_dir)/test/lookup_key_test.cc',
      '<(libaddressinput_dir)/test/lookup_key_util_test.cc',
      '<(libaddressinput_dir)/test/metadata_loader_test.cc',
      '<(libaddressinput_dir)/test/metadata_query_task_test.cc',
      '<(libaddressinput_dir)/test/null_storage_test.cc',
      '<(libaddressinput_dir)/test/post_box_matchers_test.cc',
      '<(libaddressinput_dir)/test/region_data_constants_test.cc',
      '<(libaddressinput_dir)/test/retriever_test.cc',
      '<(libaddressinput_dir)/test/rule_retriever_test.cc',
      '<(libaddressinput_dir)/test/rule_test.cc',
      '<(libaddressinput_dir)/test/util/json_test.cc',
      '<(libaddressinput_dir)/test/util/md5_unittest.cc',
      '<(libaddressinput_dir)/test/util/scoped_ptr_unittest.cc',
      '<(libaddressinput_dir)/test/util/string_split_unittest.cc',
      '<(libaddressinput_dir)/test/validating_storage_test.cc',
      '<(libaddressinput_dir)/test/validating_util_test.cc',
      '<(libaddressinput_dir)/test/validation_task_test.cc',
    ],
  },
}
