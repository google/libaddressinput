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
      u8R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      u8R"("zipex":"ASCN 1ZZ",)"
      u8R"("languages":"en")"
      "}"},
  {"AD", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"AD100,AD501,AD700",)"
      u8R"("posturl":"http://www.correos.es/comun/CodigosPostales/1010_s-CodPostal.asp?Provincia=",)"
      u8R"("languages":"ca")"
      "}"},
  {"AE", "{"
      u8R"("fmt":"%N%n%O%n%A%n%S",)"
      u8R"("lfmt":"%N%n%O%n%A%n%S",)"
      u8R"("require":"AS",)"
      u8R"("state_name_type":"emirate",)"
      u8R"("languages":"ar")"
      "}"},
  {"AF", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      u8R"("zipex":"1001,2601,3801",)"
      u8R"("languages":"fa~ps~uz-Arab~tk~bal")"
      "}"},
  {"AG", "{"
      u8R"("require":"A",)"
      u8R"("languages":"en")"
      "}"},
  {"AI", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      u8R"("zipex":"2640",)"
      u8R"("languages":"en")"
      "}"},
  {"AL", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z%n%C",)"
      u8R"("zipex":"1001,1017,3501",)"
      u8R"("languages":"sq")"
      "}"},
  {"AM", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z%n%C%n%S",)"
      u8R"("lfmt":"%N%n%O%n%A%n%Z%n%C%n%S",)"
      u8R"("zipex":"375010,0002,0010",)"
      u8R"("languages":"hy")"
      "}"},
  {"AO", "{"
      u8R"("languages":"pt")"
      "}"},
  {"AQ", "{"
      "}"},
  {"AR", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C%n%S",)"
      u8R"("zipex":"C1070AAM,C1000WAM,B1000TBU,X5187XAB",)"
      u8R"("posturl":"http://www.correoargentino.com.ar/formularios/cpa",)"
      u8R"("languages":"es")"
      "}"},
  {"AS", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %S %Z",)"
      u8R"("require":"ACSZ",)"
      u8R"("zip_name_type":"zip",)"
      u8R"("state_name_type":"state",)"
      u8R"("zipex":"96799",)"
      u8R"("posturl":"http://zip4.usps.com/zip4/welcome.jsp",)"
      u8R"("languages":"sm~en")"
      "}"},
  {"AT", "{"
      u8R"("fmt":"%O%n%N%n%A%n%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"1010,3741",)"
      u8R"("posturl":"http://www.post.at/post_subsite_postleitzahlfinder.php",)"
      u8R"("languages":"de~hr~sl~hu")"
      "}"},
  {"AU", "{"
      u8R"("fmt":"%O%n%N%n%A%n%C %S %Z",)"
      u8R"("require":"ACSZ",)"
      u8R"("state_name_type":"state",)"
      u8R"("locality_name_type":"suburb",)"
      u8R"("zipex":"2060,3171,6430,4000,4006,3001",)"
      u8R"("posturl":"http://www1.auspost.com.au/postcodes/",)"
      u8R"("languages":"en")"
      "}"},
  {"AW", "{"
      u8R"("languages":"nl~pap")"
      "}"},
  {"AX", "{"
      u8R"("fmt":"%O%n%N%n%A%nAX-%Z %C%nÅLAND",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"22150,22550,22240,22710,22270,22730,22430",)"
      u8R"("posturl":"https://www.alandpost.ax/privat/skicka-brev/postnummer-pa-aland/postnummersokning",)"
      u8R"("languages":"sv")"
      "}"},
  {"AZ", "{"
      u8R"("fmt":"%N%n%O%n%A%nAZ %Z %C",)"
      u8R"("zipex":"1000",)"
      u8R"("languages":"az~az-Cyrl")"
      "}"},
  {"BA", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"71000",)"
      u8R"("languages":"bs~bs-Cyrl~hr~sr~sr-Latn")"
      "}"},
  {"BB", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C, %S %Z",)"
      u8R"("state_name_type":"parish",)"
      u8R"("zipex":"BB23026,BB22025",)"
      u8R"("languages":"en")"
      "}"},
  {"BD", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C - %Z",)"
      u8R"("zipex":"1340,1000",)"
      u8R"("posturl":"http://www.bangladeshpost.gov.bd/PostCode.asp",)"
      u8R"("languages":"bn")"
      "}"},
  {"BE", "{"
      u8R"("fmt":"%O%n%N%n%A%n%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"4000,1000",)"
      u8R"("posturl":"http://www.post.be/site/nl/residential/customerservice/search/postal_codes.html",)"
      u8R"("languages":"nl~fr~de")"
      "}"},
  {"BF", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %X",)"
      u8R"("languages":"fr")"
      "}"},
  {"BG", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"1000,1700",)"
      u8R"("posturl":"http://www.bgpost.bg/?cid=5",)"
      u8R"("languages":"bg")"
      "}"},
  {"BH", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      u8R"("zipex":"317",)"
      u8R"("languages":"ar")"
      "}"},
  {"BI", "{"
      u8R"("languages":"rn~fr~en")"
      "}"},
  {"BJ", "{"
      u8R"("languages":"fr")"
      "}"},
  {"BL", "{"
      u8R"("fmt":"%O%n%N%n%A%n%Z %C %X",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"97100",)"
      u8R"("posturl":"http://www.laposte.fr/Particulier/Utiliser-nos-outils-pratiques/Outils-et-documents/Trouvez-un-code-postal",)"
      u8R"("languages":"fr")"
      "}"},
  {"BM", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      u8R"("zipex":"FL 07,HM GX,HM 12",)"
      u8R"("posturl":"http://www.landvaluation.bm/",)"
      u8R"("languages":"en")"
      "}"},
  {"BN", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      u8R"("zipex":"BT2328,KA1131,BA1511",)"
      u8R"("posturl":"http://www.post.gov.bn/SitePages/postcodes.aspx",)"
      u8R"("languages":"ms~ms-Arab")"
      "}"},
  {"BO", "{"
      u8R"("languages":"es~qu~ay")"
      "}"},
  {"BQ", "{"
      u8R"("languages":"nl")"
      "}"},
  {"BR", "{"
      u8R"("fmt":"%O%n%N%n%A%n%D%n%C-%S%n%Z",)"
      u8R"("require":"ASCZ",)"
      u8R"("state_name_type":"state",)"
      u8R"("sublocality_name_type":"neighborhood",)"
      u8R"("zipex":"40301-110,70002-900",)"
      u8R"("posturl":"http://www.buscacep.correios.com.br/",)"
      u8R"("languages":"pt")"
      "}"},
  {"BS", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C, %S",)"
      u8R"("state_name_type":"island",)"
      u8R"("languages":"en")"
      "}"},
  {"BT", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      u8R"("zipex":"11001,31101,35003",)"
      u8R"("posturl":"http://www.bhutanpost.bt/postcodes/",)"
      u8R"("languages":"dz")"
      "}"},
  {"BV", "{"
      "}"},
  {"BW", "{"
      u8R"("languages":"en~tn")"
      "}"},
  {"BY", "{"
      u8R"("fmt":"%S%n%Z %C%n%A%n%O%n%N",)"
      u8R"("zipex":"223016,225860,220050",)"
      u8R"("posturl":"http://ex.belpost.by/addressbook/",)"
      u8R"("languages":"be~ru")"
      "}"},
  {"BZ", "{"
      u8R"("languages":"en")"
      "}"},
  {"CA", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %S %Z",)"
      u8R"("require":"ACSZ",)"
      u8R"("zipex":"H3Z 2Y7,V8X 3X4,T0L 1K0,T0H 1A0,K1A 0B1",)"
      u8R"("posturl":"https://www.canadapost.ca/cpo/mc/personal/postalcode/fpc.jsf",)"
      u8R"("languages":"en~fr")"
      "}"},
  {"CC", "{"
      u8R"("fmt":"%O%n%N%n%A%n%C %S %Z",)"
      u8R"("zipex":"6799",)"
      u8R"("languages":"en")"
      "}"},
  {"CD", "{"
      u8R"("languages":"sw~lua~fr~ln~kg")"
      "}"},
  {"CF", "{"
      u8R"("languages":"fr~sg")"
      "}"},
  {"CG", "{"
      u8R"("languages":"fr")"
      "}"},
  {"CH", "{"
      u8R"("fmt":"%O%n%N%n%A%nCH-%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"2544,1211,1556,3030",)"
      u8R"("posturl":"http://www.post.ch/db/owa/pv_plz_pack/pr_main",)"
      u8R"("languages":"de~gsw~fr~it~rm")"
      "}"},
  {"CI", "{"
      u8R"("fmt":"%N%n%O%n%X %A %C %X",)"
      u8R"("languages":"fr")"
      "}"},
  {"CK", "{"
      u8R"("languages":"en")"
      "}"},
  {"CL", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C%n%S",)"
      u8R"("zipex":"8340457,8720019,1230000,8329100",)"
      u8R"("posturl":"http://www.correos.cl/SitePages/home.aspx",)"
      u8R"("languages":"es")"
      "}"},
  {"CM", "{"
      u8R"("languages":"fr~en")"
      "}"},
  {"CN", "{"
      u8R"("fmt":"%Z%n%S%C%D%n%A%n%O%n%N",)"
      u8R"("lfmt":"%N%n%O%n%A%n%D%n%C%n%S, %Z",)"
      u8R"("require":"ACSZ",)"
      u8R"("sublocality_name_type":"district",)"
      u8R"("zipex":"266033,317204,100096,100808",)"
      u8R"("posturl":"http://www.ems.com.cn/serviceguide/you_bian_cha_xun.html",)"
      u8R"("languages":"zh")"
      "}"},
  {"CO", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C, %S, %Z",)"
      u8R"("require":"AS",)"
      u8R"("state_name_type":"department",)"
      u8R"("zipex":"111221,130001,760011",)"
      u8R"("posturl":"http://www.codigopostal.gov.co/",)"
      u8R"("languages":"es")"
      "}"},
  {"CR", "{"
      u8R"("fmt":"%N%n%O%n%A%n%S, %C%n%Z",)"
      u8R"("require":"ACS",)"
      u8R"("zipex":"1000,2010,1001",)"
      u8R"("posturl":"https://www.correos.go.cr/nosotros/codigopostal/busqueda.html",)"
      u8R"("languages":"es")"
      "}"},
  {"CU", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %S%n%Z",)"
      u8R"("zipex":"10700",)"
      u8R"("languages":"es")"
      "}"},
  {"CV", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C%n%S",)"
      u8R"("state_name_type":"island",)"
      u8R"("zipex":"7600",)"
      u8R"("languages":"pt")"
      "}"},
  {"CW", "{"
      u8R"("languages":"pap~nl")"
      "}"},
  {"CX", "{"
      u8R"("fmt":"%O%n%N%n%A%n%C %S %Z",)"
      u8R"("zipex":"6798",)"
      u8R"("languages":"en")"
      "}"},
  {"CY", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"2008,3304,1900",)"
      u8R"("languages":"el~tr")"
      "}"},
  {"CZ", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"100 00,251 66,530 87,110 00,225 99",)"
      u8R"("posturl":"http://psc.ceskaposta.cz/CleanForm.action",)"
      u8R"("languages":"cs")"
      "}"},
  {"DE", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"26133,53225",)"
      u8R"("posturl":"http://www.postdirekt.de/plzserver/",)"
      u8R"("languages":"de")"
      "}"},
  {"DJ", "{"
      u8R"("languages":"ar~fr")"
      "}"},
  {"DK", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"8660,1566",)"
      u8R"("posturl":"http://www.postdanmark.dk/da/Privat/Kundeservice/postnummerkort/Sider/Find-postnummer.aspx",)"
      u8R"("languages":"da~de~kl")"
      "}"},
  {"DM", "{"
      u8R"("languages":"en")"
      "}"},
  {"DO", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"11903,10101",)"
      u8R"("posturl":"http://inposdom.gob.do/codigo-postal/",)"
      u8R"("languages":"es")"
      "}"},
  {"DZ", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"40304,16027",)"
      u8R"("languages":"ar~fr")"
      "}"},
  {"EC", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z%n%C",)"
      u8R"("zipex":"090105,092301",)"
      u8R"("posturl":"http://www.codigopostal.gob.ec/",)"
      u8R"("languages":"es~qu")"
      "}"},
  {"EE", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"69501,11212",)"
      u8R"("posturl":"https://www.omniva.ee/era/sihtnumbrite_otsing",)"
      u8R"("languages":"et")"
      "}"},
  {"EG", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%S%n%Z",)"
      u8R"("lfmt":"%N%n%O%n%A%n%C%n%S%n%Z",)"
      u8R"("zipex":"12411,11599",)"
      u8R"("languages":"ar")"
      "}"},
  {"EH", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"70000,72000",)"
      u8R"("languages":"ar")"
      "}"},
  {"ER", "{"
      u8R"("languages":"ti~en~ar")"
      "}"},
  {"ES", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C %S",)"
      u8R"("require":"ACSZ",)"
      u8R"("zipex":"28039,28300,28070",)"
      u8R"("posturl":"http://www.correos.es/contenido/13-MenuRec2/04-MenuRec24/1010_s-CodPostal.asp",)"
      u8R"("languages":"es~ca~gl~eu")"
      "}"},
  {"ET", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"1000",)"
      u8R"("languages":"am")"
      "}"},
  {"FI", "{"
      u8R"("fmt":"%O%n%N%n%A%nFI-%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"00550,00011",)"
      u8R"("posturl":"https://support.posti.fi/fi/tyokalut/postinumerohaku.html",)"
      u8R"("languages":"fi~sv")"
      "}"},
  {"FJ", "{"
      u8R"("languages":"en~hif~fj")"
      "}"},
  {"FK", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"FIQQ 1ZZ",)"
      u8R"("languages":"en")"
      "}"},
  {"FM", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %S %Z",)"
      u8R"("require":"ACSZ",)"
      u8R"("zip_name_type":"zip",)"
      u8R"("state_name_type":"state",)"
      u8R"("zipex":"96941,96944",)"
      u8R"("posturl":"http://zip4.usps.com/zip4/welcome.jsp",)"
      u8R"("languages":"en")"
      "}"},
  {"FO", "{"
      u8R"("fmt":"%N%n%O%n%A%nFO%Z %C",)"
      u8R"("zipex":"100",)"
      u8R"("posturl":"http://www.postur.fo/",)"
      u8R"("languages":"fo")"
      "}"},
  {"FR", "{"
      u8R"("fmt":"%O%n%N%n%A%n%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"33380,34092,33506",)"
      u8R"("posturl":"http://www.laposte.fr/Particulier/Utiliser-nos-outils-pratiques/Outils-et-documents/Trouvez-un-code-postal",)"
      u8R"("languages":"fr")"
      "}"},
  {"GA", "{"
      u8R"("languages":"fr")"
      "}"},
  {"GB", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      u8R"("require":"ACZ",)"
      u8R"("locality_name_type":"post_town",)"
      u8R"("zipex":"EC1Y 8SY,GIR 0AA,M2 5BQ,M34 4AB,CR0 2YR,DN16 9AA,W1A 4ZZ,EC1A 1HQ,OX14 4PG,BS18 8HF,NR25 7HG,RH6 0NP,BH23 6AA,B6 5BA,SO23 9AP,PO1 3AX,BFPO 61",)"
      u8R"("posturl":"http://www.royalmail.com/postcode-finder",)"
      u8R"("languages":"en~cy~gd~ga")"
      "}"},
  {"GD", "{"
      u8R"("languages":"en")"
      "}"},
  {"GE", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"0101",)"
      u8R"("posturl":"http://www.georgianpost.ge/index.php?page=10",)"
      u8R"("languages":"ka~ab~os")"
      "}"},
  {"GF", "{"
      u8R"("fmt":"%O%n%N%n%A%n%Z %C %X",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"97300",)"
      u8R"("posturl":"http://www.laposte.fr/Particulier/Utiliser-nos-outils-pratiques/Outils-et-documents/Trouvez-un-code-postal",)"
      u8R"("languages":"fr")"
      "}"},
  {"GG", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%nGUERNSEY%n%Z",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"GY1 1AA,GY2 2BT",)"
      u8R"("posturl":"http://www.guernseypost.com/postcode_finder/",)"
      u8R"("languages":"en")"
      "}"},
  {"GH", "{"
      u8R"("languages":"ak~en~ee~gaa")"
      "}"},
  {"GI", "{"
      u8R"("fmt":"%N%n%O%n%A%nGIBRALTAR%n%Z",)"
      u8R"("require":"A",)"
      u8R"("zipex":"GX11 1AA",)"
      u8R"("languages":"en")"
      "}"},
  {"GL", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"3900,3950,3911",)"
      u8R"("languages":"kl")"
      "}"},
  {"GM", "{"
      u8R"("languages":"en")"
      "}"},
  {"GN", "{"
      u8R"("fmt":"%N%n%O%n%Z %A %C",)"
      u8R"("zipex":"001,200,100",)"
      u8R"("languages":"fr")"
      "}"},
  {"GP", "{"
      u8R"("fmt":"%O%n%N%n%A%n%Z %C %X",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"97100",)"
      u8R"("posturl":"http://www.laposte.fr/Particulier/Utiliser-nos-outils-pratiques/Outils-et-documents/Trouvez-un-code-postal",)"
      u8R"("languages":"fr")"
      "}"},
  {"GQ", "{"
      u8R"("languages":"es~fr~pt")"
      "}"},
  {"GR", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"151 24,151 10,101 88",)"
      u8R"("posturl":"http://www.elta.gr/findapostcode.aspx",)"
      u8R"("languages":"el")"
      "}"},
  {"GS", "{"
      u8R"("fmt":"%N%n%O%n%A%n%n%C%n%Z",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"SIQQ 1ZZ")"
      "}"},
  {"GT", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z- %C",)"
      u8R"("zipex":"09001,01501",)"
      u8R"("languages":"es~quc")"
      "}"},
  {"GU", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      u8R"("require":"ACZ",)"
      u8R"("zip_name_type":"zip",)"
      u8R"("zipex":"96910,96931",)"
      u8R"("posturl":"http://zip4.usps.com/zip4/welcome.jsp",)"
      u8R"("languages":"en~ch")"
      "}"},
  {"GW", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"1000,1011",)"
      u8R"("languages":"pt")"
      "}"},
  {"GY", "{"
      u8R"("languages":"en")"
      "}"},
  {"HK", "{"
      u8R"("fmt":"%S%n%C%n%A%n%O%n%N",)"
      u8R"("lfmt":"%N%n%O%n%A%n%C%n%S",)"
      u8R"("require":"AS",)"
      u8R"("state_name_type":"area",)"
      u8R"("locality_name_type":"district",)"
      u8R"("languages":"zh-Hant~en")"
      "}"},
  {"HM", "{"
      u8R"("fmt":"%O%n%N%n%A%n%C %S %Z",)"
      u8R"("zipex":"7050")"
      "}"},
  {"HN", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C, %S%n%Z",)"
      u8R"("require":"ACS",)"
      u8R"("zipex":"31301",)"
      u8R"("languages":"es")"
      "}"},
  {"HR", "{"
      u8R"("fmt":"%N%n%O%n%A%nHR-%Z %C",)"
      u8R"("zipex":"10000,21001,10002",)"
      u8R"("posturl":"http://www.posta.hr/default.aspx?pretpum",)"
      u8R"("languages":"hr~it")"
      "}"},
  {"HT", "{"
      u8R"("fmt":"%N%n%O%n%A%nHT%Z %C",)"
      u8R"("zipex":"6120,5310,6110,8510",)"
      u8R"("languages":"ht~fr")"
      "}"},
  {"HU", "{"
      u8R"("fmt":"%N%n%O%n%C%n%A%n%Z",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"1037,2380,1540",)"
      u8R"("posturl":"http://posta.hu/ugyfelszolgalat/iranyitoszam_kereso",)"
      u8R"("languages":"hu")"
      "}"},
  {"ID", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%S %Z",)"
      u8R"("require":"AS",)"
      u8R"("zipex":"40115",)"
      u8R"("languages":"id")"
      "}"},
  {"IE", "{"
      u8R"("fmt":"%N%n%O%n%A%n%D%n%C%n%S %Z",)"
      u8R"("zip_name_type":"eircode",)"
      u8R"("state_name_type":"county",)"
      u8R"("sublocality_name_type":"townland",)"
      u8R"("zipex":"A65 F4E2",)"
      u8R"("posturl":"https://finder.eircode.ie",)"
      u8R"("languages":"en")"
      "}"},
  {"IL", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      u8R"("zipex":"9614303",)"
      u8R"("posturl":"http://www.israelpost.co.il/zipcode.nsf/demozip?openform",)"
      u8R"("languages":"iw~ar")"
      "}"},
  {"IM", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"IM2 1AA,IM99 1PS",)"
      u8R"("posturl":"https://www.iompost.com/tools-forms/postcode-finder/",)"
      u8R"("languages":"en~gv")"
      "}"},
  {"IN", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z%n%S",)"
      u8R"("require":"ACSZ",)"
      u8R"("zip_name_type":"pin",)"
      u8R"("state_name_type":"state",)"
      u8R"("zipex":"110034,110001",)"
      u8R"("posturl":"https://www.indiapost.gov.in/vas/pages/FindPinCode.aspx",)"
      u8R"("languages":"en~hi")"
      "}"},
  {"IO", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"BBND 1ZZ",)"
      u8R"("languages":"en")"
      "}"},
  {"IQ", "{"
      u8R"("fmt":"%O%n%N%n%A%n%C, %S%n%Z",)"
      u8R"("require":"ACS",)"
      u8R"("zipex":"31001",)"
      u8R"("languages":"ar~ckb~az-Arab")"
      "}"},
  {"IR", "{"
      u8R"("fmt":"%O%n%N%n%S%n%C, %D%n%A%n%Z",)"
      u8R"("sublocality_name_type":"neighborhood",)"
      u8R"("zipex":"11936-12345",)"
      u8R"("languages":"fa")"
      "}"},
  {"IS", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"320,121,220,110",)"
      u8R"("posturl":"http://www.postur.is/einstaklingar/posthus/postnumer/",)"
      u8R"("languages":"is")"
      "}"},
  {"IT", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C %S",)"
      u8R"("require":"ACSZ",)"
      u8R"("zipex":"00144,47037,39049",)"
      u8R"("posturl":"http://www.poste.it/online/cercacap/",)"
      u8R"("languages":"it")"
      "}"},
  {"JE", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%nJERSEY%n%Z",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"JE1 1AA,JE2 2BT",)"
      u8R"("posturl":"http://www.jerseypost.com/tools/postcode-address-finder/",)"
      u8R"("languages":"en")"
      "}"},
  {"JM", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%S %X",)"
      u8R"("require":"ACS",)"
      u8R"("state_name_type":"parish",)"
      u8R"("languages":"en")"
      "}"},
  {"JO", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      u8R"("zipex":"11937,11190",)"
      u8R"("languages":"ar")"
      "}"},
  {"JP", "{"
      u8R"("fmt":"〒%Z%n%S%n%A%n%O%n%N",)"
      u8R"("lfmt":"%N%n%O%n%A, %S%n%Z",)"
      u8R"("require":"ASZ",)"
      u8R"("state_name_type":"prefecture",)"
      u8R"("zipex":"154-0023,350-1106,951-8073,112-0001,208-0032,231-0012",)"
      u8R"("posturl":"http://www.post.japanpost.jp/zipcode/",)"
      u8R"("languages":"ja")"
      "}"},
  {"KE", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      u8R"("zipex":"20100,00100",)"
      u8R"("languages":"sw~en")"
      "}"},
  {"KG", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"720001",)"
      u8R"("languages":"ky~ru")"
      "}"},
  {"KH", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      u8R"("zipex":"12203,14206,12000",)"
      u8R"("languages":"km")"
      "}"},
  {"KI", "{"
      u8R"("fmt":"%N%n%O%n%A%n%S%n%C",)"
      u8R"("state_name_type":"island",)"
      u8R"("languages":"en~gil")"
      "}"},
  {"KM", "{"
      u8R"("languages":"ar~fr~zdj~wni")"
      "}"},
  {"KN", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C, %S",)"
      u8R"("require":"ACS",)"
      u8R"("state_name_type":"island",)"
      u8R"("languages":"en")"
      "}"},
  {"KP", "{"
      u8R"("fmt":"%Z%n%S%n%C%n%A%n%O%n%N",)"
      u8R"("lfmt":"%N%n%O%n%A%n%C%n%S, %Z",)"
      u8R"("languages":"ko")"
      "}"},
  {"KR", "{"
      u8R"("fmt":"%S %C%D%n%A%n%O%n%N%n%Z",)"
      u8R"("lfmt":"%N%n%O%n%A%n%D%n%C%n%S%n%Z",)"
      u8R"("require":"ACSZ",)"
      u8R"("state_name_type":"do_si",)"
      u8R"("sublocality_name_type":"district",)"
      u8R"("zipex":"03051",)"
      u8R"("posturl":"http://www.epost.go.kr/search/zipcode/search5.jsp",)"
      u8R"("languages":"ko")"
      "}"},
  {"KW", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"54541,54551,54404,13009",)"
      u8R"("languages":"ar")"
      "}"},
  {"KY", "{"
      u8R"("fmt":"%N%n%O%n%A%n%S %Z",)"
      u8R"("require":"AS",)"
      u8R"("state_name_type":"island",)"
      u8R"("zipex":"KY1-1100,KY1-1702,KY2-2101",)"
      u8R"("posturl":"http://www.caymanpost.gov.ky/",)"
      u8R"("languages":"en")"
      "}"},
  {"KZ", "{"
      u8R"("fmt":"%Z%n%S%n%C%n%A%n%O%n%N",)"
      u8R"("zipex":"040900,050012",)"
      u8R"("languages":"ru~kk")"
      "}"},
  {"LA", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"01160,01000",)"
      u8R"("languages":"lo")"
      "}"},
  {"LB", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      u8R"("zipex":"2038 3054,1107 2810,1000",)"
      u8R"("languages":"ar")"
      "}"},
  {"LC", "{"
      u8R"("languages":"en")"
      "}"},
  {"LI", "{"
      u8R"("fmt":"%O%n%N%n%A%nFL-%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"9496,9491,9490,9485",)"
      u8R"("posturl":"http://www.post.ch/db/owa/pv_plz_pack/pr_main",)"
      u8R"("languages":"de~gsw")"
      "}"},
  {"LK", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      u8R"("zipex":"20000,00100",)"
      u8R"("posturl":"http://www.slpost.gov.lk/",)"
      u8R"("languages":"si~ta")"
      "}"},
  {"LR", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"1000",)"
      u8R"("languages":"en")"
      "}"},
  {"LS", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      u8R"("zipex":"100",)"
      u8R"("languages":"st~en")"
      "}"},
  {"LT", "{"
      u8R"("fmt":"%O%n%N%n%A%nLT-%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"04340,03500",)"
      u8R"("posturl":"http://www.post.lt/lt/?id=316",)"
      u8R"("languages":"lt")"
      "}"},
  {"LU", "{"
      u8R"("fmt":"%O%n%N%n%A%nL-%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"4750,2998",)"
      u8R"("posturl":"https://www.post.lu/fr/grandes-entreprises/solutions-postales/rechercher-un-code-postal",)"
      u8R"("languages":"fr~lb~de")"
      "}"},
  {"LV", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C, %Z",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"LV-1073,LV-1000",)"
      u8R"("posturl":"http://www.pasts.lv/lv/uzzinas/nodalas/",)"
      u8R"("languages":"lv")"
      "}"},
  {"LY", "{"
      u8R"("languages":"ar")"
      "}"},
  {"MA", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"53000,10000,20050,16052",)"
      u8R"("languages":"ar~fr~tzm")"
      "}"},
  {"MC", "{"
      u8R"("fmt":"%N%n%O%n%A%nMC-%Z %C %X",)"
      u8R"("zipex":"98000,98020,98011,98001",)"
      u8R"("languages":"fr")"
      "}"},
  {"MD", "{"
      u8R"("fmt":"%N%n%O%n%A%nMD-%Z %C",)"
      u8R"("zipex":"2012,2019",)"
      u8R"("languages":"ro")"
      "}"},
  {"ME", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"81257,81258,81217,84314,85366",)"
      u8R"("languages":"sr-Latn")"
      "}"},
  {"MF", "{"
      u8R"("fmt":"%O%n%N%n%A%n%Z %C %X",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"97100",)"
      u8R"("posturl":"https://www.laposte.fr/particulier/outils/trouver-un-code-postal",)"
      u8R"("languages":"fr")"
      "}"},
  {"MG", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"501,101",)"
      u8R"("languages":"mg~fr~en")"
      "}"},
  {"MH", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %S %Z",)"
      u8R"("require":"ACSZ",)"
      u8R"("zip_name_type":"zip",)"
      u8R"("state_name_type":"state",)"
      u8R"("zipex":"96960,96970",)"
      u8R"("posturl":"http://zip4.usps.com/zip4/welcome.jsp",)"
      u8R"("languages":"en~mh")"
      "}"},
  {"MK", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"1314,1321,1443,1062",)"
      u8R"("languages":"mk~sq")"
      "}"},
  {"ML", "{"
      u8R"("languages":"fr")"
      "}"},
  {"MM", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C, %Z",)"
      u8R"("zipex":"11181",)"
      u8R"("languages":"my")"
      "}"},
  {"MN", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%S %Z",)"
      u8R"("zipex":"65030,65270",)"
      u8R"("posturl":"http://www.zipcode.mn/",)"
      u8R"("languages":"mn")"
      "}"},
  {"MO", "{"
      u8R"("fmt":"%A%n%O%n%N",)"
      u8R"("lfmt":"%N%n%O%n%A",)"
      u8R"("require":"A",)"
      u8R"("languages":"zh-Hant~pt")"
      "}"},
  {"MP", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %S %Z",)"
      u8R"("require":"ACSZ",)"
      u8R"("zip_name_type":"zip",)"
      u8R"("state_name_type":"state",)"
      u8R"("zipex":"96950,96951,96952",)"
      u8R"("posturl":"http://zip4.usps.com/zip4/welcome.jsp",)"
      u8R"("languages":"en")"
      "}"},
  {"MQ", "{"
      u8R"("fmt":"%O%n%N%n%A%n%Z %C %X",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"97220",)"
      u8R"("posturl":"http://www.laposte.fr/Particulier/Utiliser-nos-outils-pratiques/Outils-et-documents/Trouvez-un-code-postal",)"
      u8R"("languages":"fr")"
      "}"},
  {"MR", "{"
      u8R"("languages":"ar")"
      "}"},
  {"MS", "{"
      u8R"("languages":"en")"
      "}"},
  {"MT", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      u8R"("zipex":"NXR 01,ZTN 05,GPO 01,BZN 1130,SPB 6031,VCT 1753",)"
      u8R"("posturl":"https://www.maltapost.com/PostCode/",)"
      u8R"("languages":"mt~en")"
      "}"},
  {"MU", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z%n%C",)"
      u8R"("zipex":"42602",)"
      u8R"("languages":"en~fr")"
      "}"},
  {"MV", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      u8R"("zipex":"20026",)"
      u8R"("posturl":"http://www.maldivespost.com/?lid=10",)"
      u8R"("languages":"dv")"
      "}"},
  {"MW", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %X",)"
      u8R"("languages":"en~ny")"
      "}"},
  {"MX", "{"
      u8R"("fmt":"%N%n%O%n%A%n%D%n%Z %C, %S",)"
      u8R"("require":"ACSZ",)"
      u8R"("state_name_type":"state",)"
      u8R"("sublocality_name_type":"neighborhood",)"
      u8R"("zipex":"02860,77520,06082",)"
      u8R"("posturl":"https://www.correosdemexico.gob.mx/SSLServicios/ConsultaCP/Descarga.aspx",)"
      u8R"("languages":"es")"
      "}"},
  {"MY", "{"
      u8R"("fmt":"%N%n%O%n%A%n%D%n%Z %C%n%S",)"
      u8R"("require":"ACZ",)"
      u8R"("state_name_type":"state",)"
      u8R"("sublocality_name_type":"village_township",)"
      u8R"("zipex":"43000,50754,88990,50670",)"
      u8R"("posturl":"http://www.pos.com.my",)"
      u8R"("languages":"ms")"
      "}"},
  {"MZ", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C%S",)"
      u8R"("zipex":"1102,1119,3212",)"
      u8R"("languages":"pt")"
      "}"},
  {"NA", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Cn%Z",)"
      u8R"("zipex":"10001,10017",)"
      u8R"("languages":"en")"
      "}"},
  {"NC", "{"
      u8R"("fmt":"%O%n%N%n%A%n%Z %C %X",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"98814,98800,98810",)"
      u8R"("posturl":"http://poste.opt.nc/index.php?option=com_content&view=article&id=80&Itemid=131",)"
      u8R"("languages":"fr")"
      "}"},
  {"NE", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"8001",)"
      u8R"("languages":"fr")"
      "}"},
  {"NF", "{"
      u8R"("fmt":"%O%n%N%n%A%n%C %S %Z",)"
      u8R"("zipex":"2899",)"
      u8R"("languages":"en")"
      "}"},
  {"NG", "{"
      u8R"("fmt":"%N%n%O%n%A%n%D%n%C %Z%n%S",)"
      u8R"("state_name_type":"state",)"
      u8R"("zipex":"930283,300001,931104",)"
      u8R"("posturl":"http://www.nigeriapostcodes.com/",)"
      u8R"("languages":"en")"
      "}"},
  {"NI", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z%n%C, %S",)"
      u8R"("state_name_type":"department",)"
      u8R"("zipex":"52000",)"
      u8R"("posturl":"http://www.correos.gob.ni/index.php/codigo-postal-2",)"
      u8R"("languages":"es")"
      "}"},
  {"NL", "{"
      u8R"("fmt":"%O%n%N%n%A%n%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"1234 AB,2490 AA",)"
      u8R"("posturl":"http://www.postnl.nl/voorthuis/",)"
      u8R"("languages":"nl~fy")"
      "}"},
  {"NO", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("locality_name_type":"post_town",)"
      u8R"("zipex":"0025,0107,6631",)"
      u8R"("posturl":"http://adressesok.posten.no/nb/postal_codes/search",)"
      u8R"("languages":"no~nn~se")"
      "}"},
  {"NP", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      u8R"("zipex":"44601",)"
      u8R"("posturl":"http://www.gpo.gov.np/Home/Postalcode",)"
      u8R"("languages":"ne")"
      "}"},
  {"NR", "{"
      u8R"("fmt":"%N%n%O%n%A%n%S",)"
      u8R"("require":"AS",)"
      u8R"("state_name_type":"district",)"
      u8R"("languages":"en")"
      "}"},
  {"NU", "{"
      u8R"("languages":"en~niu")"
      "}"},
  {"NZ", "{"
      u8R"("fmt":"%N%n%O%n%A%n%D%n%C %Z",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"6001,6015,6332,8252,1030",)"
      u8R"("posturl":"http://www.nzpost.co.nz/Cultures/en-NZ/OnlineTools/PostCodeFinder/",)"
      u8R"("languages":"en~mi")"
      "}"},
  {"OM", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z%n%C",)"
      u8R"("zipex":"133,112,111",)"
      u8R"("languages":"ar")"
      "}"},
  {"PA", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%S",)"
      u8R"("languages":"es")"
      "}"},
  {"PE", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z%n%S",)"
      u8R"("locality_name_type":"district",)"
      u8R"("zipex":"LIMA 23,LIMA 42,CALLAO 2,02001",)"
      u8R"("posturl":"http://www.serpost.com.pe/cpostal/codigo",)"
      u8R"("languages":"es")"
      "}"},
  {"PF", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C %S",)"
      u8R"("require":"ACSZ",)"
      u8R"("state_name_type":"island",)"
      u8R"("zipex":"98709",)"
      u8R"("languages":"fr~ty")"
      "}"},
  {"PG", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z %S",)"
      u8R"("require":"ACS",)"
      u8R"("zipex":"111",)"
      u8R"("languages":"tpi~en~ho")"
      "}"},
  {"PH", "{"
      u8R"("fmt":"%N%n%O%n%A%n%D, %C%n%Z %S",)"
      u8R"("zipex":"1008,1050,1135,1207,2000,1000",)"
      u8R"("posturl":"http://www.philpost.gov.ph/",)"
      u8R"("languages":"en")"
      "}"},
  {"PK", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C-%Z",)"
      u8R"("zipex":"44000",)"
      u8R"("posturl":"http://www.pakpost.gov.pk/postcode.php",)"
      u8R"("languages":"ur~en")"
      "}"},
  {"PL", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"00-950,05-470,48-300,32-015,00-940",)"
      u8R"("posturl":"http://kody.poczta-polska.pl/",)"
      u8R"("languages":"pl~de~csb~lt")"
      "}"},
  {"PM", "{"
      u8R"("fmt":"%O%n%N%n%A%n%Z %C %X",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"97500",)"
      u8R"("languages":"fr")"
      "}"},
  {"PN", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"PCRN 1ZZ",)"
      u8R"("languages":"en")"
      "}"},
  {"PR", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C PR %Z",)"
      u8R"("require":"ACZ",)"
      u8R"("zip_name_type":"zip",)"
      u8R"("zipex":"00930",)"
      u8R"("posturl":"http://zip4.usps.com/zip4/welcome.jsp",)"
      u8R"("languages":"es~en")"
      "}"},
  {"PS", "{"
      u8R"("languages":"ar")"
      "}"},
  {"PT", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"2725-079,1250-096,1201-950,2860-571,1208-148",)"
      u8R"("posturl":"http://www.ctt.pt/feapl_2/app/open/tools.jspx?tool=1",)"
      u8R"("languages":"pt")"
      "}"},
  {"PW", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %S %Z",)"
      u8R"("require":"ACSZ",)"
      u8R"("zip_name_type":"zip",)"
      u8R"("state_name_type":"state",)"
      u8R"("zipex":"96940",)"
      u8R"("posturl":"http://zip4.usps.com/zip4/welcome.jsp",)"
      u8R"("languages":"pau~en")"
      "}"},
  {"PY", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"1536,1538,1209",)"
      u8R"("languages":"gn~es")"
      "}"},
  {"QA", "{"
      u8R"("languages":"ar")"
      "}"},
  {"RE", "{"
      u8R"("fmt":"%O%n%N%n%A%n%Z %C %X",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"97400",)"
      u8R"("posturl":"http://www.laposte.fr/Particulier/Utiliser-nos-outils-pratiques/Outils-et-documents/Trouvez-un-code-postal",)"
      u8R"("languages":"fr")"
      "}"},
  {"RO", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"060274,061357,200716",)"
      u8R"("posturl":"http://www.posta-romana.ro/zip_codes",)"
      u8R"("languages":"ro")"
      "}"},
  {"RS", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"106314",)"
      u8R"("posturl":"http://www.posta.rs/struktura/lat/aplikacije/pronadji/nadji-postu.asp",)"
      u8R"("languages":"sr~sr-Latn~hu~ro~hr~sk~uk")"
      "}"},
  {"RU", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%S%n%Z",)"
      u8R"("lfmt":"%N%n%O%n%A%n%C%n%S%n%Z",)"
      u8R"("require":"ACSZ",)"
      u8R"("state_name_type":"oblast",)"
      u8R"("zipex":"247112,103375,188300",)"
      u8R"("posturl":"https://www.pochta.ru/post-index",)"
      u8R"("languages":"ru")"
      "}"},
  {"RW", "{"
      u8R"("languages":"rw~en~fr")"
      "}"},
  {"SA", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      u8R"("zipex":"11564,11187,11142",)"
      u8R"("languages":"ar")"
      "}"},
  {"SB", "{"
      u8R"("languages":"en")"
      "}"},
  {"SC", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%S",)"
      u8R"("state_name_type":"island",)"
      u8R"("languages":"fr~en")"
      "}"},
  {"SD", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      u8R"("locality_name_type":"district",)"
      u8R"("zipex":"11042,11113",)"
      u8R"("languages":"ar~en")"
      "}"},
  {"SE", "{"
      u8R"("fmt":"%O%n%N%n%A%nSE-%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("locality_name_type":"post_town",)"
      u8R"("zipex":"11455,12345,10500",)"
      u8R"("posturl":"https://www.postnord.se/online-verktyg/verktyg/sok/sok-postnummer-och-adress",)"
      u8R"("languages":"sv~fi")"
      "}"},
  {"SG", "{"
      u8R"("fmt":"%N%n%O%n%A%nSINGAPORE %Z",)"
      u8R"("require":"AZ",)"
      u8R"("zipex":"546080,308125,408600",)"
      u8R"("posturl":"https://www.singpost.com/find-postal-code",)"
      u8R"("languages":"en~zh~ms~ta")"
      "}"},
  {"SH", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"STHL 1ZZ",)"
      u8R"("languages":"en")"
      "}"},
  {"SI", "{"
      u8R"("fmt":"%N%n%O%n%A%nSI-%Z %C",)"
      u8R"("zipex":"4000,1001,2500",)"
      u8R"("languages":"sl")"
      "}"},
  {"SJ", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("locality_name_type":"post_town",)"
      u8R"("zipex":"9170",)"
      u8R"("posturl":"http://epab.posten.no/",)"
      u8R"("languages":"no")"
      "}"},
  {"SK", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"010 01,023 14,972 48,921 01,975 99",)"
      u8R"("posturl":"http://psc.posta.sk",)"
      u8R"("languages":"sk")"
      "}"},
  {"SL", "{"
      u8R"("languages":"en")"
      "}"},
  {"SM", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("require":"AZ",)"
      u8R"("zipex":"47890,47891,47895,47899",)"
      u8R"("posturl":"http://www.poste.it/online/cercacap/",)"
      u8R"("languages":"it")"
      "}"},
  {"SN", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"12500,46024,16556,10000",)"
      u8R"("languages":"wo~fr~ff~srr~dyo~sav~mfv~bjt~snf~knf~bsc~mey~tnr")"
      "}"},
  {"SO", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C, %S %Z",)"
      u8R"("require":"ACS",)"
      u8R"("zipex":"JH 09010,AD 11010",)"
      u8R"("languages":"so")"
      "}"},
  {"SR", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%S",)"
      u8R"("languages":"nl")"
      "}"},
  {"SS", "{"
      u8R"("languages":"en")"
      "}"},
  {"ST", "{"
      u8R"("languages":"pt")"
      "}"},
  {"SV", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z-%C%n%S",)"
      u8R"("require":"ACS",)"
      u8R"("zipex":"CP 1101",)"
      u8R"("languages":"es")"
      "}"},
  {"SX", "{"
      u8R"("languages":"en~nl")"
      "}"},
  {"SY", "{"
      u8R"("locality_name_type":"district",)"
      u8R"("languages":"ar~fr")"
      "}"},
  {"SZ", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      u8R"("zipex":"H100",)"
      u8R"("posturl":"http://www.sptc.co.sz/swazipost/codes/index.php",)"
      u8R"("languages":"en~ss")"
      "}"},
  {"TA", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      u8R"("zipex":"TDCU 1ZZ",)"
      u8R"("languages":"en")"
      "}"},
  {"TC", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"TKCA 1ZZ",)"
      u8R"("languages":"en")"
      "}"},
  {"TD", "{"
      u8R"("languages":"fr~ar")"
      "}"},
  {"TF", "{"
      u8R"("languages":"fr")"
      "}"},
  {"TG", "{"
      u8R"("languages":"fr")"
      "}"},
  {"TH", "{"
      u8R"("fmt":"%N%n%O%n%A%n%D %C%n%S %Z",)"
      u8R"("lfmt":"%N%n%O%n%A%n%D, %C%n%S %Z",)"
      u8R"("zipex":"10150,10210",)"
      u8R"("languages":"th")"
      "}"},
  {"TJ", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"735450,734025",)"
      u8R"("languages":"tg")"
      "}"},
  {"TK", "{"
      u8R"("languages":"en~tkl")"
      "}"},
  {"TL", "{"
      u8R"("languages":"pt~tet")"
      "}"},
  {"TM", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"744000",)"
      u8R"("languages":"tk")"
      "}"},
  {"TN", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"1002,8129,3100,1030",)"
      u8R"("posturl":"http://www.poste.tn/codes.php",)"
      u8R"("languages":"ar~fr")"
      "}"},
  {"TO", "{"
      u8R"("languages":"to~en")"
      "}"},
  {"TR", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C/%S",)"
      u8R"("require":"ACZ",)"
      u8R"("locality_name_type":"district",)"
      u8R"("zipex":"01960,06101",)"
      u8R"("posturl":"http://postakodu.ptt.gov.tr/",)"
      u8R"("languages":"tr")"
      "}"},
  {"TT", "{"
      u8R"("languages":"en")"
      "}"},
  {"TV", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%S",)"
      u8R"("state_name_type":"island",)"
      u8R"("languages":"tyv")"
      "}"},
  {"TW", "{"
      u8R"("fmt":"%Z%n%S%C%n%A%n%O%n%N",)"
      u8R"("lfmt":"%N%n%O%n%A%n%C, %S %Z",)"
      u8R"("require":"ACSZ",)"
      u8R"("state_name_type":"county",)"
      u8R"("zipex":"104,106,10603,40867",)"
      u8R"("posturl":"http://www.post.gov.tw/post/internet/f_searchzone/index.jsp?ID=190102",)"
      u8R"("languages":"zh-Hant")"
      "}"},
  {"TZ", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"6090,34413",)"
      u8R"("languages":"sw~en")"
      "}"},
  {"UA", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%S%n%Z",)"
      u8R"("lfmt":"%N%n%O%n%A%n%C%n%S%n%Z",)"
      u8R"("require":"ACSZ",)"
      u8R"("state_name_type":"oblast",)"
      u8R"("zipex":"15432,01055,01001",)"
      u8R"("posturl":"http://services.ukrposhta.com/postindex_new/",)"
      u8R"("languages":"uk")"
      "}"},
  {"UG", "{"
      u8R"("languages":"sw~en")"
      "}"},
  {"UM", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %S %Z",)"
      u8R"("require":"ACS",)"
      u8R"("zip_name_type":"zip",)"
      u8R"("state_name_type":"state",)"
      u8R"("zipex":"96898",)"
      u8R"("posturl":"http://zip4.usps.com/zip4/welcome.jsp",)"
      u8R"("languages":"en")"
      "}"},
  {"US", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C, %S %Z",)"
      u8R"("require":"ACSZ",)"
      u8R"("zip_name_type":"zip",)"
      u8R"("state_name_type":"state",)"
      u8R"("zipex":"95014,22162-1010",)"
      u8R"("posturl":"https://tools.usps.com/go/ZipLookupAction!input.action",)"
      u8R"("languages":"en")"
      "}"},
  {"UY", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C %S",)"
      u8R"("zipex":"11600",)"
      u8R"("posturl":"http://www.correo.com.uy/index.asp?codPag=codPost&switchMapa=codPost",)"
      u8R"("languages":"es")"
      "}"},
  {"UZ", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C%n%S",)"
      u8R"("zipex":"702100,700000",)"
      u8R"("posturl":"http://www.pochta.uz/ru/uslugi/indexsearch.html",)"
      u8R"("languages":"uz~uz-Cyrl")"
      "}"},
  {"VA", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"00120",)"
      u8R"("languages":"it")"
      "}"},
  {"VC", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      u8R"("zipex":"VC0100,VC0110,VC0400",)"
      u8R"("posturl":"http://www.svgpost.gov.vc/?option=com_content&view=article&id=3&Itemid=16",)"
      u8R"("languages":"en")"
      "}"},
  {"VE", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z, %S",)"
      u8R"("require":"ACS",)"
      u8R"("state_name_type":"state",)"
      u8R"("zipex":"1010,3001,8011,1020",)"
      u8R"("posturl":"http://postcode.vnpost.vn/services/search.aspx",)"
      u8R"("languages":"es")"
      "}"},
  {"VG", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      u8R"("require":"A",)"
      u8R"("zipex":"VG1110,VG1150,VG1160",)"
      u8R"("languages":"en")"
      "}"},
  {"VI", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %S %Z",)"
      u8R"("require":"ACSZ",)"
      u8R"("zip_name_type":"zip",)"
      u8R"("state_name_type":"state",)"
      u8R"("zipex":"00802-1222,00850-9802",)"
      u8R"("posturl":"http://zip4.usps.com/zip4/welcome.jsp",)"
      u8R"("languages":"en")"
      "}"},
  {"VN", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%S %Z",)"
      u8R"("lfmt":"%N%n%O%n%A%n%C%n%S %Z",)"
      u8R"("zipex":"70010,55999",)"
      u8R"("posturl":"http://postcode.vnpost.vn/services/search.aspx",)"
      u8R"("languages":"vi")"
      "}"},
  {"VU", "{"
      u8R"("languages":"bi~en~fr")"
      "}"},
  {"WF", "{"
      u8R"("fmt":"%O%n%N%n%A%n%Z %C %X",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"98600",)"
      u8R"("languages":"fr")"
      "}"},
  {"WS", "{"
      u8R"("languages":"sm~en")"
      "}"},
  {"XK", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"10000",)"
      u8R"("languages":"sq~sr~sr-Latn")"
      "}"},
  {"YE", "{"
      u8R"("languages":"ar")"
      "}"},
  {"YT", "{"
      u8R"("fmt":"%O%n%N%n%A%n%Z %C %X",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"97600",)"
      u8R"("languages":"fr")"
      "}"},
  {"ZA", "{"
      u8R"("fmt":"%N%n%O%n%A%n%D%n%C%n%Z",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"0083,1451,0001",)"
      u8R"("posturl":"https://www.postoffice.co.za/Questions/postalcode.html",)"
      u8R"("languages":"en~zu~xh~af~nso~tn~st~ts~ss~ve~nr")"
      "}"},
  {"ZM", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"50100,50101",)"
      u8R"("languages":"en")"
      "}"},
  {"ZW", "{"
      u8R"("languages":"sn~en~nd")"
      "}"},
  };

}  // namespace

// static
const std::string& RegionDataConstants::GetDefaultRegionData() {
  static const std::string kDefaultRegionData(
      "{"
      u8R"("fmt":"%N%n%O%n%A%n%C",)"
      u8R"("require":"AC",)"
      u8R"("zip_name_type":"postal",)"
      u8R"("state_name_type":"province",)"
      u8R"("locality_name_type":"city",)"
      u8R"("sublocality_name_type":"suburb")"
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
