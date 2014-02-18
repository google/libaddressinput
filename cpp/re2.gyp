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
    're2_dir%': '/usr/include',
    're2_lib%': '-lre2',
  },
  'targets': [
    {
      'target_name': 're2',
      'type': 'none',
      'all_dependent_settings': {
        'include_dirs': [
          '<(re2_dir)',
        ],
        'libraries': [
          '<(re2_lib)',
        ],
      },
    },
  ],
}
