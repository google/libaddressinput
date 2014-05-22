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
    'libaddressinput_files': [
      'src/address_data.cc',
      'src/address_field.cc',
      'src/address_field_util.cc',
      'src/address_formatter.cc',
      'src/address_problem.cc',
      'src/address_ui.cc',
      'src/address_validator.cc',
      'src/format_element.cc',
      'src/language.cc',
      'src/localization.cc',
      'src/lookup_key.cc',
      'src/lookup_key_util.cc',
      'src/metadata_loader.cc',
      'src/metadata_query_task.cc',
      'src/null_storage.cc',
      'src/post_box_matchers.cc',
      'src/preload_supplier.cc',
      'src/region_data_constants.cc',
      'src/retriever.cc',
      'src/rule.cc',
      'src/rule_retriever.cc',
      'src/util/json.cc',
      'src/util/md5.cc',
      'src/util/string_compare.cc',
      'src/util/string_split.cc',
      'src/util/string_util.cc',
      'src/validating_storage.cc',
      'src/validating_util.cc',
      'src/validation_task.cc',
    ],
    'libaddressinput_test_files': [
      'test/address_data_test.cc',
      'test/address_field_test.cc',
      'test/address_field_util_test.cc',
      'test/address_formatter_test.cc',
      'test/address_problem_test.cc',
      'test/address_ui_test.cc',
      'test/address_validator_test.cc',
      'test/fake_downloader.cc',
      'test/fake_downloader_test.cc',
      'test/fake_storage.cc',
      'test/fake_storage_test.cc',
      'test/format_element_test.cc',
      'test/language_test.cc',
      'test/localization_test.cc',
      'test/lookup_key_test.cc',
      'test/lookup_key_util_test.cc',
      'test/metadata_loader_test.cc',
      'test/metadata_query_task_test.cc',
      'test/null_storage_test.cc',
      'test/post_box_matchers_test.cc',
      'test/region_data_constants_test.cc',
      'test/retriever_test.cc',
      'test/rule_retriever_test.cc',
      'test/rule_test.cc',
      'test/supplier_test.cc',
      'test/util/json_test.cc',
      'test/util/md5_unittest.cc',
      'test/util/scoped_ptr_unittest.cc',
      'test/util/string_compare_test.cc',
      'test/util/string_split_unittest.cc',
      'test/util/string_util_test.cc',
      'test/validating_storage_test.cc',
      'test/validating_util_test.cc',
      'test/validation_task_test.cc',
    ],
  },
}