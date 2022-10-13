// Copyright (C) 2013 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// AUTOMATICALLY GENERATED FILE - DO NOT EDIT

#include "region_data_constants.h"

#include <libaddressinput/address_field.h>

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <map>
#include <string>
#include <vector>

#include "address_field_util.h"
#include "format_element.h"
#include "lookup_key.h"
#include "util/size.h"

namespace i18n {
namespace addressinput {
namespace {

struct RegionData {
  const char* const region_code;
  const char* const data;
};

const RegionData kRegionData[] = {
  {"AC", "{"
      R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      R"("zipex":"ASCN 1ZZ",)"
      R"("languages":"en")"
      "}"},
  {"AD", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("zipex":"AD100,AD501,AD700",)"
      R"("posturl":"http://www.correos.es/comun/CodigosPostales/1010_s-CodPostal.asp?Provincia=",)"
      R"("languages":"ca")"
      "}"},
  {"AE", "{"
      R"("fmt":"%N%n%O%n%A%n%S",)"
      R"("lfmt":"%N%n%O%n%A%n%S",)"
      R"("require":"AS",)"
      R"("state_name_type":"emirate",)"
      R"("languages":"ar")"
      "}"},
  {"AF", "{"
      R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      R"("zipex":"1001,2601,3801",)"
      R"("languages":"fa~ps~uz-Arab~tk")"
      "}"},
  {"AG", "{"
      R"("require":"A",)"
      R"("languages":"en")"
      "}"},
  {"AI", "{"
      R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      R"("zipex":"2640",)"
      R"("languages":"en")"
      "}"},
  {"AL", "{"
      R"("fmt":"%N%n%O%n%A%n%Z%n%C",)"
      R"("zipex":"1001,1017,3501",)"
      R"("languages":"sq")"
      "}"},
  {"AM", "{"
      R"("fmt":"%N%n%O%n%A%n%Z%n%C%n%S",)"
      R"("lfmt":"%N%n%O%n%A%n%Z%n%C%n%S",)"
      R"("zipex":"375010,0002,0010",)"
      R"("languages":"hy")"
      "}"},
  {"AO", "{"
      R"("languages":"pt")"
      "}"},
  {"AQ", "{"
      "}"},
  {"AR", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C%n%S",)"
      R"("zipex":"C1070AAM,C1000WAM,B1000TBU,X5187XAB",)"
      R"("posturl":"http://www.correoargentino.com.ar/formularios/cpa",)"
      R"("languages":"es")"
      "}"},
  {"AS", "{"
      R"("fmt":"%N%n%O%n%A%n%C %S %Z",)"
      R"("require":"ACSZ",)"
      R"("zip_name_type":"zip",)"
      R"("state_name_type":"state",)"
      R"("zipex":"96799",)"
      R"("posturl":"http://zip4.usps.com/zip4/welcome.jsp",)"
      R"("languages":"sm~en")"
      "}"},
  {"AT", "{"
      R"("fmt":"%O%n%N%n%A%n%Z %C",)"
      R"("require":"ACZ",)"
      R"("zipex":"1010,3741",)"
      R"("posturl":"http://www.post.at/post_subsite_postleitzahlfinder.php",)"
      R"("languages":"de~hr~sl~hu")"
      "}"},
  {"AU", "{"
      R"("fmt":"%O%n%N%n%A%n%C %S %Z",)"
      R"("require":"ACSZ",)"
      R"("state_name_type":"state",)"
      R"("locality_name_type":"suburb",)"
      R"("zipex":"2060,3171,6430,4000,4006,3001",)"
      R"("posturl":"http://www1.auspost.com.au/postcodes/",)"
      R"("languages":"en")"
      "}"},
  {"AW", "{"
      R"("languages":"nl~pap")"
      "}"},
  {"AX", "{"
      R"("fmt":"%O%n%N%n%A%nAX-%Z %C%nÅLAND",)"
      R"("require":"ACZ",)"
      R"("zipex":"22150,22550,22240,22710,22270,22730,22430",)"
      R"("posturl":"https://www.alandpost.ax/privat/skicka-brev/postnummer-pa-aland/postnummersokning",)"
      R"("languages":"sv")"
      "}"},
  {"AZ", "{"
      R"("fmt":"%N%n%O%n%A%nAZ %Z %C",)"
      R"("zipex":"1000",)"
      R"("languages":"az~az-Cyrl")"
      "}"},
  {"BA", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("zipex":"71000",)"
      R"("languages":"bs~bs-Cyrl~hr~sr~sr-Latn")"
      "}"},
  {"BB", "{"
      R"("fmt":"%N%n%O%n%A%n%C, %S %Z",)"
      R"("state_name_type":"parish",)"
      R"("zipex":"BB23026,BB22025",)"
      R"("languages":"en")"
      "}"},
  {"BD", "{"
      R"("fmt":"%N%n%O%n%A%n%C - %Z",)"
      R"("zipex":"1340,1000",)"
      R"("posturl":"https://bdpost.portal.gov.bd/site/page/f41a42bd-2540-4afa-8568-af56443c3df8/-",)"
      R"("languages":"bn")"
      "}"},
  {"BE", "{"
      R"("fmt":"%O%n%N%n%A%n%Z %C",)"
      R"("require":"ACZ",)"
      R"("zipex":"4000,1000",)"
      R"("posturl":"http://www.post.be/site/nl/residential/customerservice/search/postal_codes.html",)"
      R"("languages":"nl~fr~de")"
      "}"},
  {"BF", "{"
      R"("fmt":"%N%n%O%n%A%n%C %X",)"
      R"("languages":"fr")"
      "}"},
  {"BG", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("zipex":"1000,1700",)"
      R"("posturl":"http://www.bgpost.bg/?cid=5",)"
      R"("languages":"bg")"
      "}"},
  {"BH", "{"
      R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      R"("zipex":"317",)"
      R"("languages":"ar")"
      "}"},
  {"BI", "{"
      R"("languages":"rn~fr~en")"
      "}"},
  {"BJ", "{"
      R"("languages":"fr")"
      "}"},
  {"BL", "{"
      R"("fmt":"%O%n%N%n%A%n%Z %C %X",)"
      R"("require":"ACZ",)"
      R"("zipex":"97100",)"
      R"("posturl":"http://www.laposte.fr/Particulier/Utiliser-nos-outils-pratiques/Outils-et-documents/Trouvez-un-code-postal",)"
      R"("languages":"fr")"
      "}"},
  {"BM", "{"
      R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      R"("zipex":"FL 07,HM GX,HM 12",)"
      R"("posturl":"http://www.landvaluation.bm/",)"
      R"("languages":"en")"
      "}"},
  {"BN", "{"
      R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      R"("zipex":"BT2328,KA1131,BA1511",)"
      R"("posturl":"http://www.post.gov.bn/SitePages/postcodes.aspx",)"
      R"("languages":"ms~ms-Arab")"
      "}"},
  {"BO", "{"
      R"("languages":"es~qu~ay")"
      "}"},
  {"BQ", "{"
      R"("languages":"nl")"
      "}"},
  {"BR", "{"
      R"("fmt":"%O%n%N%n%A%n%D%n%C-%S%n%Z",)"
      R"("require":"ASCZ",)"
      R"("state_name_type":"state",)"
      R"("sublocality_name_type":"neighborhood",)"
      R"("zipex":"40301-110,70002-900",)"
      R"("posturl":"http://www.buscacep.correios.com.br/",)"
      R"("languages":"pt")"
      "}"},
  {"BS", "{"
      R"("fmt":"%N%n%O%n%A%n%C, %S",)"
      R"("state_name_type":"island",)"
      R"("languages":"en")"
      "}"},
  {"BT", "{"
      R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      R"("zipex":"11001,31101,35003",)"
      R"("posturl":"http://www.bhutanpost.bt/postcodes/",)"
      R"("languages":"dz")"
      "}"},
  {"BV", "{"
      "}"},
  {"BW", "{"
      R"("languages":"en~tn")"
      "}"},
  {"BY", "{"
      R"("fmt":"%O%n%N%n%A%n%Z, %C%n%S",)"
      R"("zipex":"223016,225860,220050",)"
      R"("posturl":"http://ex.belpost.by/addressbook/",)"
      R"("languages":"be~ru")"
      "}"},
  {"BZ", "{"
      R"("languages":"en")"
      "}"},
  {"CA", "{"
      R"("fmt":"%N%n%O%n%A%n%C %S %Z",)"
      R"("require":"ACSZ",)"
      R"("zipex":"H3Z 2Y7,V8X 3X4,T0L 1K0,T0H 1A0,K1A 0B1",)"
      R"("posturl":"https://www.canadapost.ca/cpo/mc/personal/postalcode/fpc.jsf",)"
      R"("languages":"en~fr")"
      "}"},
  {"CC", "{"
      R"("fmt":"%O%n%N%n%A%n%C %S %Z",)"
      R"("zipex":"6799",)"
      R"("languages":"en")"
      "}"},
  {"CD", "{"
      R"("languages":"sw~lua~fr~ln~kg")"
      "}"},
  {"CF", "{"
      R"("languages":"fr~sg")"
      "}"},
  {"CG", "{"
      R"("languages":"fr")"
      "}"},
  {"CH", "{"
      R"("fmt":"%O%n%N%n%A%nCH-%Z %C",)"
      R"("require":"ACZ",)"
      R"("zipex":"2544,1211,1556,3030",)"
      R"("posturl":"http://www.post.ch/db/owa/pv_plz_pack/pr_main",)"
      R"("languages":"de~gsw~fr~it~rm")"
      "}"},
  {"CI", "{"
      R"("fmt":"%N%n%O%n%X %A %C %X",)"
      R"("languages":"fr")"
      "}"},
  {"CK", "{"
      R"("languages":"en")"
      "}"},
  {"CL", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C%n%S",)"
      R"("zipex":"8340457,8720019,1230000,8329100",)"
      R"("posturl":"https://www.correos.cl/web/guest/codigo-postal",)"
      R"("languages":"es")"
      "}"},
  {"CM", "{"
      R"("languages":"fr~en")"
      "}"},
  {"CN", "{"
      R"("fmt":"%Z%n%S%C%D%n%A%n%O%n%N",)"
      R"("lfmt":"%N%n%O%n%A%n%D%n%C%n%S, %Z",)"
      R"("require":"ACSZ",)"
      R"("sublocality_name_type":"district",)"
      R"("zipex":"266033,317204,100096,100808",)"
      R"("posturl":"http://www.ems.com.cn/serviceguide/you_bian_cha_xun.html",)"
      R"("languages":"zh")"
      "}"},
  {"CO", "{"
      R"("fmt":"%N%n%O%n%A%n%D%n%C, %S, %Z",)"
      R"("require":"AS",)"
      R"("state_name_type":"department",)"
      R"("zipex":"111221,130001,760011",)"
      R"("posturl":"http://www.codigopostal.gov.co/",)"
      R"("languages":"es")"
      "}"},
  {"CR", "{"
      R"("fmt":"%N%n%O%n%A%n%S, %C%n%Z",)"
      R"("require":"ACS",)"
      R"("zipex":"1000,2010,1001",)"
      R"("posturl":"https://correos.go.cr/codigo-postal/",)"
      R"("languages":"es")"
      "}"},
  {"CU", "{"
      R"("fmt":"%N%n%O%n%A%n%C %S%n%Z",)"
      R"("zipex":"10700",)"
      R"("languages":"es")"
      "}"},
  {"CV", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C%n%S",)"
      R"("state_name_type":"island",)"
      R"("zipex":"7600",)"
      R"("languages":"pt")"
      "}"},
  {"CW", "{"
      R"("languages":"pap~nl")"
      "}"},
  {"CX", "{"
      R"("fmt":"%O%n%N%n%A%n%C %S %Z",)"
      R"("zipex":"6798",)"
      R"("languages":"en")"
      "}"},
  {"CY", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("zipex":"2008,3304,1900",)"
      R"("languages":"el~tr")"
      "}"},
  {"CZ", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("require":"ACZ",)"
      R"("zipex":"100 00,251 66,530 87,110 00,225 99",)"
      R"("posturl":"http://psc.ceskaposta.cz/CleanForm.action",)"
      R"("languages":"cs")"
      "}"},
  {"DE", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("require":"ACZ",)"
      R"("zipex":"26133,53225",)"
      R"("posturl":"http://www.postdirekt.de/plzserver/",)"
      R"("languages":"de")"
      "}"},
  {"DJ", "{"
      R"("languages":"ar~fr")"
      "}"},
  {"DK", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("require":"ACZ",)"
      R"("zipex":"8660,1566",)"
      R"("posturl":"http://www.postdanmark.dk/da/Privat/Kundeservice/postnummerkort/Sider/Find-postnummer.aspx",)"
      R"("languages":"da~de~kl")"
      "}"},
  {"DM", "{"
      R"("languages":"en")"
      "}"},
  {"DO", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("zipex":"11903,10101",)"
      R"("posturl":"http://inposdom.gob.do/",)"
      R"("languages":"es")"
      "}"},
  {"DZ", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("zipex":"40304,16027",)"
      R"("languages":"ar~fr")"
      "}"},
  {"EC", "{"
      R"("fmt":"%N%n%O%n%A%n%Z%n%C",)"
      R"("zipex":"090105,092301",)"
      R"("posturl":"http://www.codigopostal.gob.ec/",)"
      R"("languages":"es~qu")"
      "}"},
  {"EE", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C %S",)"
      R"("require":"ACZ",)"
      R"("zipex":"69501,11212",)"
      R"("posturl":"https://www.omniva.ee/era/sihtnumbrite_otsing",)"
      R"("languages":"et")"
      "}"},
  {"EG", "{"
      R"("fmt":"%N%n%O%n%A%n%C%n%S%n%Z",)"
      R"("lfmt":"%N%n%O%n%A%n%C%n%S%n%Z",)"
      R"("zipex":"12411,11599",)"
      R"("languages":"ar")"
      "}"},
  {"EH", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("zipex":"70000,72000",)"
      R"("languages":"ar")"
      "}"},
  {"ER", "{"
      R"("languages":"ti~en~ar")"
      "}"},
  {"ES", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C %S",)"
      R"("require":"ACSZ",)"
      R"("zipex":"28039,28300,28070",)"
      R"("posturl":"http://www.correos.es/contenido/13-MenuRec2/04-MenuRec24/1010_s-CodPostal.asp",)"
      R"("languages":"es~ca~gl~eu")"
      "}"},
  {"ET", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("zipex":"1000",)"
      R"("languages":"am")"
      "}"},
  {"FI", "{"
      R"("fmt":"%O%n%N%n%A%nFI-%Z %C",)"
      R"("require":"ACZ",)"
      R"("zipex":"00550,00011",)"
      R"("posturl":"https://support.posti.fi/fi/tyokalut/postinumerohaku.html",)"
      R"("languages":"fi~sv")"
      "}"},
  {"FJ", "{"
      R"("languages":"en~hif~fj")"
      "}"},
  {"FK", "{"
      R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      R"("require":"ACZ",)"
      R"("zipex":"FIQQ 1ZZ",)"
      R"("languages":"en")"
      "}"},
  {"FM", "{"
      R"("fmt":"%N%n%O%n%A%n%C %S %Z",)"
      R"("require":"ACSZ",)"
      R"("zip_name_type":"zip",)"
      R"("state_name_type":"state",)"
      R"("zipex":"96941,96944",)"
      R"("posturl":"http://zip4.usps.com/zip4/welcome.jsp",)"
      R"("languages":"en")"
      "}"},
  {"FO", "{"
      R"("fmt":"%N%n%O%n%A%nFO%Z %C",)"
      R"("zipex":"100",)"
      R"("posturl":"https://www.posta.fo/fo/forsida/finn-postnr-stad/",)"
      R"("languages":"fo")"
      "}"},
  {"FR", "{"
      R"("fmt":"%O%n%N%n%A%n%Z %C",)"
      R"("require":"ACZ",)"
      R"("zipex":"33380,34092,33506",)"
      R"("posturl":"http://www.laposte.fr/Particulier/Utiliser-nos-outils-pratiques/Outils-et-documents/Trouvez-un-code-postal",)"
      R"("languages":"fr")"
      "}"},
  {"GA", "{"
      R"("languages":"fr")"
      "}"},
  {"GB", "{"
      R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      R"("require":"ACZ",)"
      R"("locality_name_type":"post_town",)"
      R"("zipex":"EC1Y 8SY,GIR 0AA,M2 5BQ,M34 4AB,CR0 2YR,DN16 9AA,W1A 4ZZ,EC1A 1HQ,OX14 4PG,BS18 8HF,NR25 7HG,RH6 0NP,BH23 6AA,B6 5BA,SO23 9AP,PO1 3AX,BFPO 61",)"
      R"("posturl":"http://www.royalmail.com/postcode-finder",)"
      R"("languages":"en~cy~ga~gd")"
      "}"},
  {"GD", "{"
      R"("languages":"en")"
      "}"},
  {"GE", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("zipex":"0101",)"
      R"("posturl":"http://www.georgianpost.ge/index.php?page=10",)"
      R"("languages":"ka~ab~os")"
      "}"},
  {"GF", "{"
      R"("fmt":"%O%n%N%n%A%n%Z %C %X",)"
      R"("require":"ACZ",)"
      R"("zipex":"97300",)"
      R"("posturl":"http://www.laposte.fr/Particulier/Utiliser-nos-outils-pratiques/Outils-et-documents/Trouvez-un-code-postal",)"
      R"("languages":"fr")"
      "}"},
  {"GG", "{"
      R"("fmt":"%N%n%O%n%A%n%C%nGUERNSEY%n%Z",)"
      R"("require":"ACZ",)"
      R"("zipex":"GY1 1AA,GY2 2BT",)"
      R"("posturl":"http://www.guernseypost.com/postcode_finder/",)"
      R"("languages":"en")"
      "}"},
  {"GH", "{"
      R"("languages":"ak~en~ee~gaa")"
      "}"},
  {"GI", "{"
      R"("fmt":"%N%n%O%n%A%nGIBRALTAR%n%Z",)"
      R"("require":"A",)"
      R"("zipex":"GX11 1AA",)"
      R"("languages":"en")"
      "}"},
  {"GL", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("require":"ACZ",)"
      R"("zipex":"3900,3950,3911",)"
      R"("languages":"kl")"
      "}"},
  {"GM", "{"
      R"("languages":"en")"
      "}"},
  {"GN", "{"
      R"("fmt":"%N%n%O%n%Z %A %C",)"
      R"("zipex":"001,200,100",)"
      R"("languages":"fr")"
      "}"},
  {"GP", "{"
      R"("fmt":"%O%n%N%n%A%n%Z %C %X",)"
      R"("require":"ACZ",)"
      R"("zipex":"97100",)"
      R"("posturl":"http://www.laposte.fr/Particulier/Utiliser-nos-outils-pratiques/Outils-et-documents/Trouvez-un-code-postal",)"
      R"("languages":"fr")"
      "}"},
  {"GQ", "{"
      R"("languages":"es~fr~pt")"
      "}"},
  {"GR", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("require":"ACZ",)"
      R"("zipex":"151 24,151 10,101 88",)"
      R"("posturl":"http://www.elta.gr/findapostcode.aspx",)"
      R"("languages":"el")"
      "}"},
  {"GS", "{"
      R"("fmt":"%N%n%O%n%A%n%n%C%n%Z",)"
      R"("require":"ACZ",)"
      R"("zipex":"SIQQ 1ZZ")"
      "}"},
  {"GT", "{"
      R"("fmt":"%N%n%O%n%A%n%Z- %C",)"
      R"("zipex":"09001,01501",)"
      R"("languages":"es~quc")"
      "}"},
  {"GU", "{"
      R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      R"("require":"ACZ",)"
      R"("zip_name_type":"zip",)"
      R"("zipex":"96910,96931",)"
      R"("posturl":"http://zip4.usps.com/zip4/welcome.jsp",)"
      R"("languages":"en~ch")"
      "}"},
  {"GW", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("zipex":"1000,1011",)"
      R"("languages":"pt")"
      "}"},
  {"GY", "{"
      R"("languages":"en")"
      "}"},
  {"HK", "{"
      R"("fmt":"%S%n%C%n%A%n%O%n%N",)"
      R"("lfmt":"%N%n%O%n%A%n%C%n%S",)"
      R"("require":"AS",)"
      R"("state_name_type":"area",)"
      R"("locality_name_type":"district",)"
      R"("languages":"zh-Hant~en")"
      "}"},
  {"HM", "{"
      R"("fmt":"%O%n%N%n%A%n%C %S %Z",)"
      R"("zipex":"7050")"
      "}"},
  {"HN", "{"
      R"("fmt":"%N%n%O%n%A%n%C, %S%n%Z",)"
      R"("require":"ACS",)"
      R"("state_name_type":"department",)"
      R"("zipex":"31301",)"
      R"("languages":"es")"
      "}"},
  {"HR", "{"
      R"("fmt":"%N%n%O%n%A%nHR-%Z %C",)"
      R"("zipex":"10000,21001,10002",)"
      R"("posturl":"http://www.posta.hr/default.aspx?pretpum",)"
      R"("languages":"hr~it")"
      "}"},
  {"HT", "{"
      R"("fmt":"%N%n%O%n%A%nHT%Z %C",)"
      R"("zipex":"6120,5310,6110,8510",)"
      R"("languages":"ht~fr")"
      "}"},
  {"HU", "{"
      R"("fmt":"%N%n%O%n%C%n%A%n%Z",)"
      R"("require":"ACZ",)"
      R"("zipex":"1037,2380,1540",)"
      R"("posturl":"http://posta.hu/ugyfelszolgalat/iranyitoszam_kereso",)"
      R"("languages":"hu")"
      "}"},
  {"ID", "{"
      R"("fmt":"%N%n%O%n%A%n%C%n%S %Z",)"
      R"("require":"AS",)"
      R"("zipex":"40115",)"
      R"("languages":"id")"
      "}"},
  {"IE", "{"
      R"("fmt":"%N%n%O%n%A%n%D%n%C%n%S%n%Z",)"
      R"("zip_name_type":"eircode",)"
      R"("state_name_type":"county",)"
      R"("sublocality_name_type":"townland",)"
      R"("zipex":"A65 F4E2",)"
      R"("posturl":"https://finder.eircode.ie",)"
      R"("languages":"en")"
      "}"},
  {"IL", "{"
      R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      R"("zipex":"9614303",)"
      R"("posturl":"http://www.israelpost.co.il/zipcode.nsf/demozip?openform",)"
      R"("languages":"iw~ar")"
      "}"},
  {"IM", "{"
      R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      R"("require":"ACZ",)"
      R"("zipex":"IM2 1AA,IM99 1PS",)"
      R"("posturl":"https://www.iompost.com/tools-forms/postcode-finder/",)"
      R"("languages":"en~gv")"
      "}"},
  {"IN", "{"
      R"("fmt":"%N%n%O%n%A%n%C %Z%n%S",)"
      R"("require":"ACSZ",)"
      R"("zip_name_type":"pin",)"
      R"("state_name_type":"state",)"
      R"("zipex":"110034,110001",)"
      R"("posturl":"https://www.indiapost.gov.in/vas/pages/FindPinCode.aspx",)"
      R"("languages":"en~hi")"
      "}"},
  {"IO", "{"
      R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      R"("require":"ACZ",)"
      R"("zipex":"BBND 1ZZ",)"
      R"("languages":"en")"
      "}"},
  {"IQ", "{"
      R"("fmt":"%O%n%N%n%A%n%C, %S%n%Z",)"
      R"("require":"ACS",)"
      R"("zipex":"31001",)"
      R"("languages":"ar~ckb~az-Arab")"
      "}"},
  {"IR", "{"
      R"("fmt":"%O%n%N%n%S%n%C, %D%n%A%n%Z",)"
      R"("sublocality_name_type":"neighborhood",)"
      R"("zipex":"11936-12345",)"
      R"("languages":"fa")"
      "}"},
  {"IS", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("zipex":"320,121,220,110",)"
      R"("posturl":"https://posturinn.is/",)"
      R"("languages":"is")"
      "}"},
  {"IT", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C %S",)"
      R"("require":"ACSZ",)"
      R"("zipex":"00144,47037,39049",)"
      R"("posturl":"http://www.poste.it/online/cercacap/",)"
      R"("languages":"it")"
      "}"},
  {"JE", "{"
      R"("fmt":"%N%n%O%n%A%n%C%nJERSEY%n%Z",)"
      R"("require":"ACZ",)"
      R"("zipex":"JE1 1AA,JE2 2BT",)"
      R"("posturl":"http://www.jerseypost.com/tools/postcode-address-finder/",)"
      R"("languages":"en")"
      "}"},
  {"JM", "{"
      R"("fmt":"%N%n%O%n%A%n%C%n%S %X",)"
      R"("require":"ACS",)"
      R"("state_name_type":"parish",)"
      R"("languages":"en")"
      "}"},
  {"JO", "{"
      R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      R"("zipex":"11937,11190",)"
      R"("languages":"ar")"
      "}"},
  {"JP", "{"
      R"("fmt":"〒%Z%n%S%n%A%n%O%n%N",)"
      R"("lfmt":"%N%n%O%n%A, %S%n%Z",)"
      R"("require":"ASZ",)"
      R"("state_name_type":"prefecture",)"
      R"("zipex":"154-0023,350-1106,951-8073,112-0001,208-0032,231-0012",)"
      R"("posturl":"http://www.post.japanpost.jp/zipcode/",)"
      R"("languages":"ja")"
      "}"},
  {"KE", "{"
      R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      R"("zipex":"20100,00100",)"
      R"("languages":"sw~en")"
      "}"},
  {"KG", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("zipex":"720001",)"
      R"("languages":"ky~ru")"
      "}"},
  {"KH", "{"
      R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      R"("zipex":"120101,120108",)"
      R"("posturl":"https://www.cambodiapost.post/page/postal-codes",)"
      R"("languages":"km")"
      "}"},
  {"KI", "{"
      R"("fmt":"%N%n%O%n%A%n%S%n%C",)"
      R"("state_name_type":"island",)"
      R"("languages":"en~gil")"
      "}"},
  {"KM", "{"
      R"("languages":"ar~fr~zdj~wni")"
      "}"},
  {"KN", "{"
      R"("fmt":"%N%n%O%n%A%n%C, %S",)"
      R"("require":"ACS",)"
      R"("state_name_type":"island",)"
      R"("languages":"en")"
      "}"},
  {"KP", "{"
      R"("fmt":"%Z%n%S%n%C%n%A%n%O%n%N",)"
      R"("lfmt":"%N%n%O%n%A%n%C%n%S, %Z",)"
      R"("languages":"ko")"
      "}"},
  {"KR", "{"
      R"("fmt":"%S %C%D%n%A%n%O%n%N%n%Z",)"
      R"("lfmt":"%N%n%O%n%A%n%D%n%C%n%S%n%Z",)"
      R"("require":"ACSZ",)"
      R"("state_name_type":"do_si",)"
      R"("sublocality_name_type":"district",)"
      R"("zipex":"03051",)"
      R"("posturl":"http://www.epost.go.kr/search/zipcode/search5.jsp",)"
      R"("languages":"ko")"
      "}"},
  {"KW", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("zipex":"54541,54551,54404,13009",)"
      R"("languages":"ar")"
      "}"},
  {"KY", "{"
      R"("fmt":"%N%n%O%n%A%n%S %Z",)"
      R"("require":"AS",)"
      R"("state_name_type":"island",)"
      R"("zipex":"KY1-1100,KY1-1702,KY2-2101",)"
      R"("posturl":"http://www.caymanpost.gov.ky/",)"
      R"("languages":"en")"
      "}"},
  {"KZ", "{"
      R"("fmt":"%Z%n%S%n%C%n%A%n%O%n%N",)"
      R"("zipex":"040900,050012",)"
      R"("languages":"ru~kk")"
      "}"},
  {"LA", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("zipex":"01160,01000",)"
      R"("languages":"lo")"
      "}"},
  {"LB", "{"
      R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      R"("zipex":"2038 3054,1107 2810,1000",)"
      R"("languages":"ar")"
      "}"},
  {"LC", "{"
      R"("languages":"en")"
      "}"},
  {"LI", "{"
      R"("fmt":"%O%n%N%n%A%nFL-%Z %C",)"
      R"("require":"ACZ",)"
      R"("zipex":"9496,9491,9490,9485",)"
      R"("posturl":"http://www.post.ch/db/owa/pv_plz_pack/pr_main",)"
      R"("languages":"de~gsw")"
      "}"},
  {"LK", "{"
      R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      R"("zipex":"20000,00100",)"
      R"("posturl":"http://www.slpost.gov.lk/",)"
      R"("languages":"si~ta")"
      "}"},
  {"LR", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("zipex":"1000",)"
      R"("languages":"en")"
      "}"},
  {"LS", "{"
      R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      R"("zipex":"100",)"
      R"("languages":"st~en")"
      "}"},
  {"LT", "{"
      R"("fmt":"%O%n%N%n%A%nLT-%Z %C %S",)"
      R"("require":"ACZ",)"
      R"("zipex":"04340,03500",)"
      R"("posturl":"http://www.post.lt/lt/?id=316",)"
      R"("languages":"lt")"
      "}"},
  {"LU", "{"
      R"("fmt":"%O%n%N%n%A%nL-%Z %C",)"
      R"("require":"ACZ",)"
      R"("zipex":"4750,2998",)"
      R"("posturl":"https://www.post.lu/fr/grandes-entreprises/solutions-postales/rechercher-un-code-postal",)"
      R"("languages":"fr~lb~de")"
      "}"},
  {"LV", "{"
      R"("fmt":"%N%n%O%n%A%n%S%n%C, %Z",)"
      R"("require":"ACZ",)"
      R"("zipex":"LV-1073,LV-1000",)"
      R"("posturl":"http://www.pasts.lv/lv/uzzinas/nodalas/",)"
      R"("languages":"lv")"
      "}"},
  {"LY", "{"
      R"("languages":"ar")"
      "}"},
  {"MA", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("zipex":"53000,10000,20050,16052",)"
      R"("languages":"ar~fr~tzm")"
      "}"},
  {"MC", "{"
      R"("fmt":"%N%n%O%n%A%nMC-%Z %C %X",)"
      R"("zipex":"98000,98020,98011,98001",)"
      R"("languages":"fr")"
      "}"},
  {"MD", "{"
      R"("fmt":"%N%n%O%n%A%nMD-%Z %C",)"
      R"("zipex":"2012,2019",)"
      R"("languages":"ro")"
      "}"},
  {"ME", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("zipex":"81257,81258,81217,84314,85366",)"
      R"("languages":"sr-Latn")"
      "}"},
  {"MF", "{"
      R"("fmt":"%O%n%N%n%A%n%Z %C %X",)"
      R"("require":"ACZ",)"
      R"("zipex":"97100",)"
      R"("posturl":"https://www.laposte.fr/particulier/outils/trouver-un-code-postal",)"
      R"("languages":"fr")"
      "}"},
  {"MG", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("zipex":"501,101",)"
      R"("languages":"mg~fr~en")"
      "}"},
  {"MH", "{"
      R"("fmt":"%N%n%O%n%A%n%C %S %Z",)"
      R"("require":"ACSZ",)"
      R"("zip_name_type":"zip",)"
      R"("state_name_type":"state",)"
      R"("zipex":"96960,96970",)"
      R"("posturl":"http://zip4.usps.com/zip4/welcome.jsp",)"
      R"("languages":"en~mh")"
      "}"},
  {"MK", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("zipex":"1314,1321,1443,1062",)"
      R"("languages":"mk~sq")"
      "}"},
  {"ML", "{"
      R"("languages":"fr")"
      "}"},
  {"MM", "{"
      R"("fmt":"%N%n%O%n%A%n%C, %Z",)"
      R"("zipex":"11181",)"
      R"("languages":"my")"
      "}"},
  {"MN", "{"
      R"("fmt":"%N%n%O%n%A%n%C%n%S %Z",)"
      R"("zipex":"65030,65270",)"
      R"("posturl":"http://www.zipcode.mn/",)"
      R"("languages":"mn")"
      "}"},
  {"MO", "{"
      R"("fmt":"%A%n%O%n%N",)"
      R"("lfmt":"%N%n%O%n%A",)"
      R"("require":"A",)"
      R"("languages":"zh-Hant~pt")"
      "}"},
  {"MP", "{"
      R"("fmt":"%N%n%O%n%A%n%C %S %Z",)"
      R"("require":"ACSZ",)"
      R"("zip_name_type":"zip",)"
      R"("state_name_type":"state",)"
      R"("zipex":"96950,96951,96952",)"
      R"("posturl":"http://zip4.usps.com/zip4/welcome.jsp",)"
      R"("languages":"en")"
      "}"},
  {"MQ", "{"
      R"("fmt":"%O%n%N%n%A%n%Z %C %X",)"
      R"("require":"ACZ",)"
      R"("zipex":"97220",)"
      R"("posturl":"http://www.laposte.fr/Particulier/Utiliser-nos-outils-pratiques/Outils-et-documents/Trouvez-un-code-postal",)"
      R"("languages":"fr")"
      "}"},
  {"MR", "{"
      R"("languages":"ar")"
      "}"},
  {"MS", "{"
      R"("languages":"en")"
      "}"},
  {"MT", "{"
      R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      R"("zipex":"NXR 01,ZTN 05,GPO 01,BZN 1130,SPB 6031,VCT 1753",)"
      R"("posturl":"https://www.maltapost.com/PostCode/",)"
      R"("languages":"mt~en")"
      "}"},
  {"MU", "{"
      R"("fmt":"%N%n%O%n%A%n%Z%n%C",)"
      R"("zipex":"42602",)"
      R"("languages":"en~fr")"
      "}"},
  {"MV", "{"
      R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      R"("zipex":"20026",)"
      R"("posturl":"http://www.maldivespost.com/?lid=10",)"
      R"("languages":"dv")"
      "}"},
  {"MW", "{"
      R"("fmt":"%N%n%O%n%A%n%C %X",)"
      R"("languages":"en~ny")"
      "}"},
  {"MX", "{"
      R"("fmt":"%N%n%O%n%A%n%D%n%Z %C, %S",)"
      R"("require":"ACSZ",)"
      R"("state_name_type":"state",)"
      R"("sublocality_name_type":"neighborhood",)"
      R"("zipex":"02860,77520,06082",)"
      R"("posturl":"https://www.correosdemexico.gob.mx/SSLServicios/ConsultaCP/Descarga.aspx",)"
      R"("languages":"es")"
      "}"},
  {"MY", "{"
      R"("fmt":"%N%n%O%n%A%n%D%n%Z %C%n%S",)"
      R"("require":"ACZ",)"
      R"("state_name_type":"state",)"
      R"("sublocality_name_type":"village_township",)"
      R"("zipex":"43000,50754,88990,50670",)"
      R"("posturl":"http://www.pos.com.my",)"
      R"("languages":"ms")"
      "}"},
  {"MZ", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C%S",)"
      R"("zipex":"1102,1119,3212",)"
      R"("languages":"pt")"
      "}"},
  {"NA", "{"
      R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      R"("zipex":"10001,10017",)"
      R"("languages":"en")"
      "}"},
  {"NC", "{"
      R"("fmt":"%O%n%N%n%A%n%Z %C %X",)"
      R"("require":"ACZ",)"
      R"("zipex":"98814,98800,98810",)"
      R"("posturl":"https://www.opt.nc/particuliers/courrier-et-colis/les-codes-postaux-de-nouvelle-caledonie",)"
      R"("languages":"fr")"
      "}"},
  {"NE", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("zipex":"8001",)"
      R"("languages":"fr")"
      "}"},
  {"NF", "{"
      R"("fmt":"%O%n%N%n%A%n%C %S %Z",)"
      R"("zipex":"2899",)"
      R"("languages":"en")"
      "}"},
  {"NG", "{"
      R"("fmt":"%N%n%O%n%A%n%D%n%C %Z%n%S",)"
      R"("state_name_type":"state",)"
      R"("zipex":"930283,300001,931104",)"
      R"("posturl":"http://www.nigeriapostcodes.com/",)"
      R"("languages":"en")"
      "}"},
  {"NI", "{"
      R"("fmt":"%N%n%O%n%A%n%Z%n%C, %S",)"
      R"("state_name_type":"department",)"
      R"("zipex":"52000",)"
      R"("posturl":"http://www.correos.gob.ni/codigo-postal/",)"
      R"("languages":"es")"
      "}"},
  {"NL", "{"
      R"("fmt":"%O%n%N%n%A%n%Z %C",)"
      R"("require":"ACZ",)"
      R"("zipex":"1234 AB,2490 AA",)"
      R"("posturl":"http://www.postnl.nl/voorthuis/",)"
      R"("languages":"nl~fy")"
      "}"},
  {"NO", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("require":"ACZ",)"
      R"("locality_name_type":"post_town",)"
      R"("zipex":"0025,0107,6631",)"
      R"("posturl":"http://adressesok.posten.no/nb/postal_codes/search",)"
      R"("languages":"no~nn~se")"
      "}"},
  {"NP", "{"
      R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      R"("zipex":"44601",)"
      R"("posturl":"http://www.gpo.gov.np/Home/Postalcode",)"
      R"("languages":"ne")"
      "}"},
  {"NR", "{"
      R"("fmt":"%N%n%O%n%A%n%S",)"
      R"("require":"AS",)"
      R"("state_name_type":"district",)"
      R"("languages":"en")"
      "}"},
  {"NU", "{"
      R"("languages":"en~niu")"
      "}"},
  {"NZ", "{"
      R"("fmt":"%N%n%O%n%A%n%D%n%C %Z",)"
      R"("require":"ACZ",)"
      R"("zipex":"6001,6015,6332,8252,1030",)"
      R"("posturl":"http://www.nzpost.co.nz/Cultures/en-NZ/OnlineTools/PostCodeFinder/",)"
      R"("languages":"en~mi")"
      "}"},
  {"OM", "{"
      R"("fmt":"%N%n%O%n%A%n%Z%n%C",)"
      R"("zipex":"133,112,111",)"
      R"("languages":"ar")"
      "}"},
  {"PA", "{"
      R"("fmt":"%N%n%O%n%A%n%C%n%S",)"
      R"("languages":"es")"
      "}"},
  {"PE", "{"
      R"("fmt":"%N%n%O%n%A%n%C %Z%n%S",)"
      R"("locality_name_type":"district",)"
      R"("zipex":"LIMA 23,LIMA 42,CALLAO 2,02001",)"
      R"("posturl":"http://www.codigopostal.gob.pe/pages/invitado/consulta.jsf",)"
      R"("languages":"es")"
      "}"},
  {"PF", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C %S",)"
      R"("require":"ACSZ",)"
      R"("state_name_type":"island",)"
      R"("zipex":"98709",)"
      R"("languages":"fr~ty")"
      "}"},
  {"PG", "{"
      R"("fmt":"%N%n%O%n%A%n%C %Z %S",)"
      R"("require":"ACS",)"
      R"("zipex":"111",)"
      R"("languages":"tpi~en~ho")"
      "}"},
  {"PH", "{"
      R"("fmt":"%N%n%O%n%A%n%D, %C%n%Z %S",)"
      R"("zipex":"1008,1050,1135,1207,2000,1000",)"
      R"("posturl":"http://www.philpost.gov.ph/",)"
      R"("languages":"en")"
      "}"},
  {"PK", "{"
      R"("fmt":"%N%n%O%n%A%n%D%n%C-%Z",)"
      R"("zipex":"44000",)"
      R"("posturl":"http://www.pakpost.gov.pk/postcode.php",)"
      R"("languages":"ur~en")"
      "}"},
  {"PL", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("require":"ACZ",)"
      R"("zipex":"00-950,05-470,48-300,32-015,00-940",)"
      R"("posturl":"http://kody.poczta-polska.pl/",)"
      R"("languages":"pl~de~csb~lt")"
      "}"},
  {"PM", "{"
      R"("fmt":"%O%n%N%n%A%n%Z %C %X",)"
      R"("require":"ACZ",)"
      R"("zipex":"97500",)"
      R"("languages":"fr")"
      "}"},
  {"PN", "{"
      R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      R"("require":"ACZ",)"
      R"("zipex":"PCRN 1ZZ",)"
      R"("languages":"en")"
      "}"},
  {"PR", "{"
      R"("fmt":"%N%n%O%n%A%n%C PR %Z",)"
      R"("require":"ACZ",)"
      R"("zip_name_type":"zip",)"
      R"("zipex":"00930",)"
      R"("posturl":"http://zip4.usps.com/zip4/welcome.jsp",)"
      R"("languages":"es~en")"
      "}"},
  {"PS", "{"
      R"("languages":"ar")"
      "}"},
  {"PT", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("require":"ACZ",)"
      R"("zipex":"2725-079,1250-096,1201-950,2860-571,1208-148",)"
      R"("posturl":"http://www.ctt.pt/feapl_2/app/open/tools.jspx?tool=1",)"
      R"("languages":"pt")"
      "}"},
  {"PW", "{"
      R"("fmt":"%N%n%O%n%A%n%C %S %Z",)"
      R"("require":"ACSZ",)"
      R"("zip_name_type":"zip",)"
      R"("state_name_type":"state",)"
      R"("zipex":"96940",)"
      R"("posturl":"http://zip4.usps.com/zip4/welcome.jsp",)"
      R"("languages":"pau~en")"
      "}"},
  {"PY", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("zipex":"1536,1538,1209",)"
      R"("languages":"gn~es")"
      "}"},
  {"QA", "{"
      R"("languages":"ar")"
      "}"},
  {"RE", "{"
      R"("fmt":"%O%n%N%n%A%n%Z %C %X",)"
      R"("require":"ACZ",)"
      R"("zipex":"97400",)"
      R"("posturl":"http://www.laposte.fr/Particulier/Utiliser-nos-outils-pratiques/Outils-et-documents/Trouvez-un-code-postal",)"
      R"("languages":"fr")"
      "}"},
  {"RO", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %S %C",)"
      R"("require":"ACZ",)"
      R"("zipex":"060274,061357,200716",)"
      R"("posturl":"http://www.posta-romana.ro/zip_codes",)"
      R"("languages":"ro")"
      "}"},
  {"RS", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("zipex":"106314",)"
      R"("posturl":"http://www.posta.rs/struktura/lat/aplikacije/pronadji/nadji-postu.asp",)"
      R"("languages":"sr~sr-Latn~hu~ro~hr~sk~uk")"
      "}"},
  {"RU", "{"
      R"("fmt":"%N%n%O%n%A%n%C%n%S%n%Z",)"
      R"("lfmt":"%N%n%O%n%A%n%C%n%S%n%Z",)"
      R"("require":"ACSZ",)"
      R"("state_name_type":"oblast",)"
      R"("zipex":"247112,103375,188300",)"
      R"("posturl":"https://www.pochta.ru/post-index",)"
      R"("languages":"ru")"
      "}"},
  {"RW", "{"
      R"("languages":"rw~en~fr")"
      "}"},
  {"SA", "{"
      R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      R"("zipex":"11564,11187,11142",)"
      R"("languages":"ar")"
      "}"},
  {"SB", "{"
      R"("languages":"en")"
      "}"},
  {"SC", "{"
      R"("fmt":"%N%n%O%n%A%n%C%n%S",)"
      R"("state_name_type":"island",)"
      R"("languages":"fr~en")"
      "}"},
  {"SD", "{"
      R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      R"("locality_name_type":"district",)"
      R"("zipex":"11042,11113",)"
      R"("languages":"ar~en")"
      "}"},
  {"SE", "{"
      R"("fmt":"%O%n%N%n%A%nSE-%Z %C",)"
      R"("require":"ACZ",)"
      R"("locality_name_type":"post_town",)"
      R"("zipex":"11455,12345,10500",)"
      R"("posturl":"https://www.postnord.se/online-verktyg/verktyg/sok/sok-postnummer-och-adress",)"
      R"("languages":"sv~fi")"
      "}"},
  {"SG", "{"
      R"("fmt":"%N%n%O%n%A%nSINGAPORE %Z",)"
      R"("require":"AZ",)"
      R"("zipex":"546080,308125,408600",)"
      R"("posturl":"https://www.singpost.com/find-postal-code",)"
      R"("languages":"en~zh~ms~ta")"
      "}"},
  {"SH", "{"
      R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      R"("require":"ACZ",)"
      R"("zipex":"STHL 1ZZ",)"
      R"("languages":"en")"
      "}"},
  {"SI", "{"
      R"("fmt":"%N%n%O%n%A%nSI-%Z %C",)"
      R"("zipex":"4000,1001,2500",)"
      R"("languages":"sl")"
      "}"},
  {"SJ", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("require":"ACZ",)"
      R"("locality_name_type":"post_town",)"
      R"("zipex":"9170",)"
      R"("posturl":"http://epab.posten.no/",)"
      R"("languages":"no")"
      "}"},
  {"SK", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("require":"ACZ",)"
      R"("zipex":"010 01,023 14,972 48,921 01,975 99",)"
      R"("posturl":"http://psc.posta.sk",)"
      R"("languages":"sk")"
      "}"},
  {"SL", "{"
      R"("languages":"en")"
      "}"},
  {"SM", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("require":"AZ",)"
      R"("zipex":"47890,47891,47895,47899",)"
      R"("posturl":"http://www.poste.it/online/cercacap/",)"
      R"("languages":"it")"
      "}"},
  {"SN", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("zipex":"12500,46024,16556,10000",)"
      R"("languages":"wo~fr~ff~srr~dyo~sav~mfv~bjt~snf~knf~bsc~mey~tnr")"
      "}"},
  {"SO", "{"
      R"("fmt":"%N%n%O%n%A%n%C, %S %Z",)"
      R"("require":"ACS",)"
      R"("zipex":"JH 09010,AD 11010",)"
      R"("languages":"so")"
      "}"},
  {"SR", "{"
      R"("fmt":"%N%n%O%n%A%n%C%n%S",)"
      R"("languages":"nl")"
      "}"},
  {"SS", "{"
      R"("languages":"en")"
      "}"},
  {"ST", "{"
      R"("languages":"pt")"
      "}"},
  {"SV", "{"
      R"("fmt":"%N%n%O%n%A%n%Z-%C%n%S",)"
      R"("require":"ACS",)"
      R"("zipex":"CP 1101",)"
      R"("languages":"es")"
      "}"},
  {"SX", "{"
      R"("languages":"en~nl")"
      "}"},
  {"SY", "{"
      R"("locality_name_type":"district",)"
      R"("languages":"ar~fr")"
      "}"},
  {"SZ", "{"
      R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      R"("zipex":"H100",)"
      R"("posturl":"http://www.sptc.co.sz/swazipost/codes/index.php",)"
      R"("languages":"en~ss")"
      "}"},
  {"TA", "{"
      R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      R"("zipex":"TDCU 1ZZ",)"
      R"("languages":"en")"
      "}"},
  {"TC", "{"
      R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      R"("require":"ACZ",)"
      R"("zipex":"TKCA 1ZZ",)"
      R"("languages":"en")"
      "}"},
  {"TD", "{"
      R"("languages":"fr~ar")"
      "}"},
  {"TF", "{"
      R"("languages":"fr")"
      "}"},
  {"TG", "{"
      R"("languages":"fr")"
      "}"},
  {"TH", "{"
      R"("fmt":"%N%n%O%n%A%n%D %C%n%S %Z",)"
      R"("lfmt":"%N%n%O%n%A%n%D, %C%n%S %Z",)"
      R"("zipex":"10150,10210",)"
      R"("languages":"th")"
      "}"},
  {"TJ", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("zipex":"735450,734025",)"
      R"("languages":"tg")"
      "}"},
  {"TK", "{"
      R"("languages":"en~tkl")"
      "}"},
  {"TL", "{"
      R"("languages":"pt~tet")"
      "}"},
  {"TM", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("zipex":"744000",)"
      R"("languages":"tk")"
      "}"},
  {"TN", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("zipex":"1002,8129,3100,1030",)"
      R"("posturl":"http://www.poste.tn/codes.php",)"
      R"("languages":"ar~fr")"
      "}"},
  {"TO", "{"
      R"("languages":"to~en")"
      "}"},
  {"TR", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C/%S",)"
      R"("require":"ACZ",)"
      R"("locality_name_type":"district",)"
      R"("zipex":"01960,06101",)"
      R"("posturl":"http://postakodu.ptt.gov.tr/",)"
      R"("languages":"tr")"
      "}"},
  {"TT", "{"
      R"("languages":"en")"
      "}"},
  {"TV", "{"
      R"("fmt":"%N%n%O%n%A%n%C%n%S",)"
      R"("state_name_type":"island",)"
      R"("languages":"tyv")"
      "}"},
  {"TW", "{"
      R"("fmt":"%Z%n%S%C%n%A%n%O%n%N",)"
      R"("lfmt":"%N%n%O%n%A%n%C, %S %Z",)"
      R"("require":"ACSZ",)"
      R"("state_name_type":"county",)"
      R"("locality_name_type":"district",)"
      R"("zipex":"104,106,10603,40867",)"
      R"("posturl":"http://www.post.gov.tw/post/internet/f_searchzone/index.jsp?ID=190102",)"
      R"("languages":"zh-Hant")"
      "}"},
  {"TZ", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("zipex":"6090,34413",)"
      R"("languages":"sw~en")"
      "}"},
  {"UA", "{"
      R"("fmt":"%N%n%O%n%A%n%C%n%S%n%Z",)"
      R"("lfmt":"%N%n%O%n%A%n%C%n%S%n%Z",)"
      R"("require":"ACZ",)"
      R"("state_name_type":"oblast",)"
      R"("zipex":"15432,01055,01001",)"
      R"("posturl":"http://services.ukrposhta.com/postindex_new/",)"
      R"("languages":"uk")"
      "}"},
  {"UG", "{"
      R"("languages":"sw~en")"
      "}"},
  {"UM", "{"
      R"("fmt":"%N%n%O%n%A%n%C %S %Z",)"
      R"("require":"ACS",)"
      R"("zip_name_type":"zip",)"
      R"("state_name_type":"state",)"
      R"("zipex":"96898",)"
      R"("posturl":"http://zip4.usps.com/zip4/welcome.jsp",)"
      R"("languages":"en")"
      "}"},
  {"US", "{"
      R"("fmt":"%N%n%O%n%A%n%C, %S %Z",)"
      R"("require":"ACSZ",)"
      R"("zip_name_type":"zip",)"
      R"("state_name_type":"state",)"
      R"("zipex":"95014,22162-1010",)"
      R"("posturl":"https://tools.usps.com/go/ZipLookupAction!input.action",)"
      R"("languages":"en")"
      "}"},
  {"UY", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C %S",)"
      R"("zipex":"11600",)"
      R"("posturl":"http://www.correo.com.uy/index.asp?codPag=codPost&switchMapa=codPost",)"
      R"("languages":"es")"
      "}"},
  {"UZ", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C%n%S",)"
      R"("zipex":"702100,700000",)"
      R"("posturl":"http://www.pochta.uz/ru/uslugi/indexsearch.html",)"
      R"("languages":"uz~uz-Cyrl")"
      "}"},
  {"VA", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("zipex":"00120",)"
      R"("languages":"it")"
      "}"},
  {"VC", "{"
      R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      R"("zipex":"VC0100,VC0110,VC0400",)"
      R"("posturl":"http://www.svgpost.gov.vc/?option=com_content&view=article&id=3&Itemid=16",)"
      R"("languages":"en")"
      "}"},
  {"VE", "{"
      R"("fmt":"%N%n%O%n%A%n%C %Z, %S",)"
      R"("require":"ACS",)"
      R"("state_name_type":"state",)"
      R"("zipex":"1010,3001,8011,1020",)"
      R"("posturl":"http://postcode.vnpost.vn/services/search.aspx",)"
      R"("languages":"es")"
      "}"},
  {"VG", "{"
      R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      R"("require":"A",)"
      R"("zipex":"VG1110,VG1150,VG1160",)"
      R"("languages":"en")"
      "}"},
  {"VI", "{"
      R"("fmt":"%N%n%O%n%A%n%C %S %Z",)"
      R"("require":"ACSZ",)"
      R"("zip_name_type":"zip",)"
      R"("state_name_type":"state",)"
      R"("zipex":"00802-1222,00850-9802",)"
      R"("posturl":"http://zip4.usps.com/zip4/welcome.jsp",)"
      R"("languages":"en")"
      "}"},
  {"VN", "{"
      R"("fmt":"%N%n%O%n%A%n%C%n%S %Z",)"
      R"("lfmt":"%N%n%O%n%A%n%C%n%S %Z",)"
      R"("zipex":"70010,55999",)"
      R"("posturl":"http://postcode.vnpost.vn/services/search.aspx",)"
      R"("languages":"vi")"
      "}"},
  {"VU", "{"
      R"("languages":"bi~en~fr")"
      "}"},
  {"WF", "{"
      R"("fmt":"%O%n%N%n%A%n%Z %C %X",)"
      R"("require":"ACZ",)"
      R"("zipex":"98600",)"
      R"("languages":"fr")"
      "}"},
  {"WS", "{"
      R"("languages":"sm~en")"
      "}"},
  {"XK", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("zipex":"10000",)"
      R"("languages":"sq~sr~sr-Latn")"
      "}"},
  {"YE", "{"
      R"("languages":"ar")"
      "}"},
  {"YT", "{"
      R"("fmt":"%O%n%N%n%A%n%Z %C %X",)"
      R"("require":"ACZ",)"
      R"("zipex":"97600",)"
      R"("languages":"fr")"
      "}"},
  {"ZA", "{"
      R"("fmt":"%N%n%O%n%A%n%D%n%C%n%Z",)"
      R"("require":"ACZ",)"
      R"("zipex":"0083,1451,0001",)"
      R"("posturl":"https://www.postoffice.co.za/Questions/postalcode.html",)"
      R"("languages":"en~zu~xh~af~nso~tn~st~ts~ss~ve~nr")"
      "}"},
  {"ZM", "{"
      R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      R"("zipex":"50100,50101",)"
      R"("languages":"en")"
      "}"},
  {"ZW", "{"
      R"("languages":"sn~en~nd")"
      "}"},
  };

}  // namespace

// static
const std::string& RegionDataConstants::GetDefaultRegionData() {
  static const std::string kDefaultRegionData(
      "{"
      R"("fmt":"%N%n%O%n%A%n%C",)"
      R"("require":"AC",)"
      R"("zip_name_type":"postal",)"
      R"("state_name_type":"province",)"
      R"("locality_name_type":"city",)"
      R"("sublocality_name_type":"suburb")"
      "}");
  return kDefaultRegionData;
}

namespace {

// Binary search over kRegionData[i].region_code values. If a match is found,
// returns true and sets |position_out| to the position of |region_code| in
// kRegionData. If a match is not found, returns false.
bool FindPositionOfRegionCode(const std::string& region_code,
                              size_t* position_out) {
  assert(position_out != nullptr);
  size_t left = 0;  // inclusive.
  size_t right = size(kRegionData);  // exclusive.
  while (left < right) {
    size_t mid = left + (right - left) / 2;
    int comparison = region_code.compare(kRegionData[mid].region_code);
    if (comparison == 0) {
      *position_out = mid;
      return true;
    } else if (comparison > 0) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }
  return false;
}

std::vector<std::string> InitRegionCodes() {
  std::vector<std::string> region_codes(size(kRegionData));
  std::transform(std::begin(kRegionData),
                 std::end(kRegionData),
                 region_codes.begin(),
                 [](const RegionData& region_data) {
                   return region_data.region_code;
                 });
  return region_codes;
}

const std::map<std::string, size_t> InitMaxLookupKeyDepth() {
  std::map<std::string, size_t> max_depth;
  for (const auto& region_data : kRegionData) {
    std::vector<FormatElement> fields;
    // Here region_data.data actually contains the entire JSON blob for this
    // region, and not only the format field, but it doesn't really matter when
    // just checking whether a particular formatting code (eg. "%C") is present,
    // as there isn't anything else in the JSON that erroneously could match a
    // formatting code.
    ParseFormatRule(region_data.data, &fields);
    size_t depth = 1;
    for (; depth < size(LookupKey::kHierarchy); ++depth) {
      AddressField field = LookupKey::kHierarchy[depth];
      // Check to see if a particular field in the hierarchy is used by
      // addresses in this country. If not, the maximum depth has been reached.
      if (std::find(fields.begin(), fields.end(), FormatElement(field)) ==
          fields.end()) {
        break;
      }
    }
    max_depth.emplace(region_data.region_code, depth - 1);
  }
  return max_depth;
}

}  // namespace

// static
bool RegionDataConstants::IsSupported(const std::string& region_code) {
  size_t unused;
  return FindPositionOfRegionCode(region_code, &unused);
}

// static
const std::vector<std::string>& RegionDataConstants::GetRegionCodes() {
  static const std::vector<std::string> kRegionCodes(InitRegionCodes());
  return kRegionCodes;
}

// static
std::string RegionDataConstants::GetRegionData(
    const std::string& region_code) {
  static const std::string kEmptyString;
  size_t position;
  bool found = FindPositionOfRegionCode(region_code, &position);
  return found ? kRegionData[position].data : kEmptyString;
}

// static
size_t RegionDataConstants::GetMaxLookupKeyDepth(
    const std::string& region_code) {
  static const std::map<std::string, size_t> kMaxDepth(InitMaxLookupKeyDepth());
  auto it = kMaxDepth.find(region_code);
  return it != kMaxDepth.end() ? it->second : 0;
}

}  // namespace addressinput
}  // namespace i18n
