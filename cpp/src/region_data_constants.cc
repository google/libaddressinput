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
#include <cstddef>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "address_field_util.h"
#include "format_element.h"
#include "lookup_key.h"
#include "util/size.h"

namespace i18n {
namespace addressinput {
namespace {

std::map<std::string, std::string> InitRegionData() {
  std::map<std::string, std::string> region_data;
  region_data.emplace("AC", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      u8R"("zipex":"ASCN 1ZZ",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("AD", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"AD100,AD501,AD700",)"
      u8R"("posturl":"http://www.correos.es/comun/CodigosPostales/1010_s-CodPostal.asp?Provincia=",)"
      u8R"("languages":"ca")"
      "}");
  region_data.emplace("AE", "{"
      u8R"("fmt":"%N%n%O%n%A%n%S",)"
      u8R"("lfmt":"%N%n%O%n%A%n%S",)"
      u8R"("require":"AS",)"
      u8R"("state_name_type":"emirate",)"
      u8R"("languages":"ar")"
      "}");
  region_data.emplace("AF", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      u8R"("zipex":"1001,2601,3801",)"
      u8R"("languages":"fa~ps~uz-Arab~tk~bal")"
      "}");
  region_data.emplace("AG", "{"
      u8R"("require":"A",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("AI", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      u8R"("zipex":"2640",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("AL", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z%n%C",)"
      u8R"("zipex":"1001,1017,3501",)"
      u8R"("languages":"sq")"
      "}");
  region_data.emplace("AM", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z%n%C%n%S",)"
      u8R"("lfmt":"%N%n%O%n%A%n%Z%n%C%n%S",)"
      u8R"("zipex":"375010,0002,0010",)"
      u8R"("languages":"hy")"
      "}");
  region_data.emplace("AO", "{"
      u8R"("languages":"pt")"
      "}");
  region_data.emplace("AQ", "{"
      "}");
  region_data.emplace("AR", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C%n%S",)"
      u8R"("zipex":"C1070AAM,C1000WAM,B1000TBU,X5187XAB",)"
      u8R"("posturl":"http://www.correoargentino.com.ar/formularios/cpa",)"
      u8R"("languages":"es")"
      "}");
  region_data.emplace("AS", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %S %Z",)"
      u8R"("require":"ACSZ",)"
      u8R"("zip_name_type":"zip",)"
      u8R"("state_name_type":"state",)"
      u8R"("zipex":"96799",)"
      u8R"("posturl":"http://zip4.usps.com/zip4/welcome.jsp",)"
      u8R"("languages":"sm~en")"
      "}");
  region_data.emplace("AT", "{"
      u8R"("fmt":"%O%n%N%n%A%n%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"1010,3741",)"
      u8R"("posturl":"http://www.post.at/post_subsite_postleitzahlfinder.php",)"
      u8R"("languages":"de~hr~sl~hu")"
      "}");
  region_data.emplace("AU", "{"
      u8R"("fmt":"%O%n%N%n%A%n%C %S %Z",)"
      u8R"("require":"ACSZ",)"
      u8R"("state_name_type":"state",)"
      u8R"("locality_name_type":"suburb",)"
      u8R"("zipex":"2060,3171,6430,4000,4006,3001",)"
      u8R"("posturl":"http://www1.auspost.com.au/postcodes/",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("AW", "{"
      u8R"("languages":"nl~pap")"
      "}");
  region_data.emplace("AX", "{"
      u8R"("fmt":"%O%n%N%n%A%nAX-%Z %C%nÅLAND",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"22150,22550,22240,22710,22270,22730,22430",)"
      u8R"("posturl":"http://www.posten.ax/department.con?iPage=123",)"
      u8R"("languages":"sv")"
      "}");
  region_data.emplace("AZ", "{"
      u8R"("fmt":"%N%n%O%n%A%nAZ %Z %C",)"
      u8R"("zipex":"1000",)"
      u8R"("languages":"az~az-Cyrl")"
      "}");
  region_data.emplace("BA", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"71000",)"
      u8R"("languages":"bs~bs-Cyrl~hr~sr~sr-Latn")"
      "}");
  region_data.emplace("BB", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C, %S %Z",)"
      u8R"("state_name_type":"parish",)"
      u8R"("zipex":"BB23026,BB22025",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("BD", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C - %Z",)"
      u8R"("zipex":"1340,1000",)"
      u8R"("posturl":"http://www.bangladeshpost.gov.bd/PostCode.asp",)"
      u8R"("languages":"bn")"
      "}");
  region_data.emplace("BE", "{"
      u8R"("fmt":"%O%n%N%n%A%n%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"4000,1000",)"
      u8R"("posturl":"http://www.post.be/site/nl/residential/customerservice/search/postal_codes.html",)"
      u8R"("languages":"nl~fr~de")"
      "}");
  region_data.emplace("BF", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %X",)"
      u8R"("languages":"fr")"
      "}");
  region_data.emplace("BG", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"1000,1700",)"
      u8R"("posturl":"http://www.bgpost.bg/?cid=5",)"
      u8R"("languages":"bg")"
      "}");
  region_data.emplace("BH", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      u8R"("zipex":"317",)"
      u8R"("languages":"ar")"
      "}");
  region_data.emplace("BI", "{"
      u8R"("languages":"rn~fr~en")"
      "}");
  region_data.emplace("BJ", "{"
      u8R"("languages":"fr")"
      "}");
  region_data.emplace("BL", "{"
      u8R"("fmt":"%O%n%N%n%A%n%Z %C %X",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"97100",)"
      u8R"("posturl":"http://www.laposte.fr/Particulier/Utiliser-nos-outils-pratiques/Outils-et-documents/Trouvez-un-code-postal",)"
      u8R"("languages":"fr")"
      "}");
  region_data.emplace("BM", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      u8R"("zipex":"FL 07,HM GX,HM 12",)"
      u8R"("posturl":"http://www.landvaluation.bm/",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("BN", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      u8R"("zipex":"BT2328,KA1131,BA1511",)"
      u8R"("posturl":"http://www.post.gov.bn/SitePages/postcodes.aspx",)"
      u8R"("languages":"ms~ms-Arab")"
      "}");
  region_data.emplace("BO", "{"
      u8R"("languages":"es~qu~ay")"
      "}");
  region_data.emplace("BQ", "{"
      u8R"("languages":"nl")"
      "}");
  region_data.emplace("BR", "{"
      u8R"("fmt":"%O%n%N%n%A%n%D%n%C-%S%n%Z",)"
      u8R"("require":"ASCZ",)"
      u8R"("state_name_type":"state",)"
      u8R"("sublocality_name_type":"neighborhood",)"
      u8R"("zipex":"40301-110,70002-900",)"
      u8R"("posturl":"http://www.buscacep.correios.com.br/",)"
      u8R"("languages":"pt")"
      "}");
  region_data.emplace("BS", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C, %S",)"
      u8R"("state_name_type":"island",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("BT", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      u8R"("zipex":"11001,31101,35003",)"
      u8R"("posturl":"http://www.bhutanpost.bt/searchpostcode.php",)"
      u8R"("languages":"dz")"
      "}");
  region_data.emplace("BV", "{"
      "}");
  region_data.emplace("BW", "{"
      u8R"("languages":"en~tn")"
      "}");
  region_data.emplace("BY", "{"
      u8R"("fmt":"%S%n%Z %C%n%A%n%O%n%N",)"
      u8R"("zipex":"223016,225860,220050",)"
      u8R"("posturl":"http://ex.belpost.by/addressbook/",)"
      u8R"("languages":"be~ru")"
      "}");
  region_data.emplace("BZ", "{"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("CA", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %S %Z",)"
      u8R"("require":"ACSZ",)"
      u8R"("zipex":"H3Z 2Y7,V8X 3X4,T0L 1K0,T0H 1A0,K1A 0B1",)"
      u8R"("posturl":"https://www.canadapost.ca/cpo/mc/personal/postalcode/fpc.jsf",)"
      u8R"("languages":"en~fr")"
      "}");
  region_data.emplace("CC", "{"
      u8R"("fmt":"%O%n%N%n%A%n%C %S %Z",)"
      u8R"("zipex":"6799",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("CD", "{"
      u8R"("languages":"sw~lua~fr~ln~kg")"
      "}");
  region_data.emplace("CF", "{"
      u8R"("languages":"fr~sg")"
      "}");
  region_data.emplace("CG", "{"
      u8R"("languages":"fr")"
      "}");
  region_data.emplace("CH", "{"
      u8R"("fmt":"%O%n%N%n%A%nCH-%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"2544,1211,1556,3030",)"
      u8R"("posturl":"http://www.post.ch/db/owa/pv_plz_pack/pr_main",)"
      u8R"("languages":"de~gsw~fr~it~rm")"
      "}");
  region_data.emplace("CI", "{"
      u8R"("fmt":"%N%n%O%n%X %A %C %X",)"
      u8R"("languages":"fr")"
      "}");
  region_data.emplace("CK", "{"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("CL", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C%n%S",)"
      u8R"("zipex":"8340457,8720019,1230000,8329100",)"
      u8R"("posturl":"http://www.correos.cl/SitePages/home.aspx",)"
      u8R"("languages":"es")"
      "}");
  region_data.emplace("CM", "{"
      u8R"("languages":"fr~en")"
      "}");
  region_data.emplace("CN", "{"
      u8R"("fmt":"%Z%n%S%C%D%n%A%n%O%n%N",)"
      u8R"("lfmt":"%N%n%O%n%A%n%D%n%C%n%S, %Z",)"
      u8R"("require":"ACSZ",)"
      u8R"("sublocality_name_type":"district",)"
      u8R"("zipex":"266033,317204,100096,100808",)"
      u8R"("posturl":"http://www.ems.com.cn/serviceguide/you_bian_cha_xun.html",)"
      u8R"("languages":"zh")"
      "}");
  region_data.emplace("CO", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C, %S, %Z",)"
      u8R"("require":"AS",)"
      u8R"("state_name_type":"department",)"
      u8R"("zipex":"111221,130001,760011",)"
      u8R"("posturl":"http://www.codigopostal.gov.co/",)"
      u8R"("languages":"es")"
      "}");
  region_data.emplace("CR", "{"
      u8R"("fmt":"%N%n%O%n%A%n%S, %C%n%Z",)"
      u8R"("require":"ACS",)"
      u8R"("zipex":"1000,2010,1001",)"
      u8R"("posturl":"https://www.correos.go.cr/nosotros/codigopostal/busqueda.html",)"
      u8R"("languages":"es")"
      "}");
  region_data.emplace("CV", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C%n%S",)"
      u8R"("state_name_type":"island",)"
      u8R"("zipex":"7600",)"
      u8R"("languages":"pt")"
      "}");
  region_data.emplace("CW", "{"
      u8R"("languages":"pap~nl")"
      "}");
  region_data.emplace("CX", "{"
      u8R"("fmt":"%O%n%N%n%A%n%C %S %Z",)"
      u8R"("zipex":"6798",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("CY", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"2008,3304,1900",)"
      u8R"("languages":"el~tr")"
      "}");
  region_data.emplace("CZ", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"100 00,251 66,530 87,110 00,225 99",)"
      u8R"("posturl":"http://psc.ceskaposta.cz/CleanForm.action",)"
      u8R"("languages":"cs")"
      "}");
  region_data.emplace("DE", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"26133,53225",)"
      u8R"("posturl":"http://www.postdirekt.de/plzserver/",)"
      u8R"("languages":"de")"
      "}");
  region_data.emplace("DJ", "{"
      u8R"("languages":"ar~fr")"
      "}");
  region_data.emplace("DK", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"8660,1566",)"
      u8R"("posturl":"http://www.postdanmark.dk/da/Privat/Kundeservice/postnummerkort/Sider/Find-postnummer.aspx",)"
      u8R"("languages":"da~de~kl")"
      "}");
  region_data.emplace("DM", "{"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("DO", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"11903,10101",)"
      u8R"("posturl":"http://inposdom.gob.do/codigo-postal/",)"
      u8R"("languages":"es")"
      "}");
  region_data.emplace("DZ", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"40304,16027",)"
      u8R"("languages":"ar~fr")"
      "}");
  region_data.emplace("EC", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z%n%C",)"
      u8R"("zipex":"090105,092301",)"
      u8R"("posturl":"http://www.codigopostal.gob.ec/",)"
      u8R"("languages":"es~qu")"
      "}");
  region_data.emplace("EE", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"69501,11212",)"
      u8R"("posturl":"https://www.omniva.ee/era/sihtnumbrite_otsing",)"
      u8R"("languages":"et")"
      "}");
  region_data.emplace("EG", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%S%n%Z",)"
      u8R"("lfmt":"%N%n%O%n%A%n%C%n%S%n%Z",)"
      u8R"("zipex":"12411,11599",)"
      u8R"("languages":"ar")"
      "}");
  region_data.emplace("EH", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"70000,72000",)"
      u8R"("languages":"ar")"
      "}");
  region_data.emplace("ER", "{"
      u8R"("languages":"ti~en~ar")"
      "}");
  region_data.emplace("ES", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C %S",)"
      u8R"("require":"ACSZ",)"
      u8R"("zipex":"28039,28300,28070",)"
      u8R"("posturl":"http://www.correos.es/contenido/13-MenuRec2/04-MenuRec24/1010_s-CodPostal.asp",)"
      u8R"("languages":"es~ca~gl~eu")"
      "}");
  region_data.emplace("ET", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"1000",)"
      u8R"("languages":"am")"
      "}");
  region_data.emplace("FI", "{"
      u8R"("fmt":"%O%n%N%n%A%nFI-%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"00550,00011",)"
      u8R"("posturl":"http://www.verkkoposti.com/e3/postinumeroluettelo",)"
      u8R"("languages":"fi~sv")"
      "}");
  region_data.emplace("FJ", "{"
      u8R"("languages":"en~hif~fj")"
      "}");
  region_data.emplace("FK", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"FIQQ 1ZZ",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("FM", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %S %Z",)"
      u8R"("require":"ACSZ",)"
      u8R"("zip_name_type":"zip",)"
      u8R"("state_name_type":"state",)"
      u8R"("zipex":"96941,96944",)"
      u8R"("posturl":"http://zip4.usps.com/zip4/welcome.jsp",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("FO", "{"
      u8R"("fmt":"%N%n%O%n%A%nFO%Z %C",)"
      u8R"("zipex":"100",)"
      u8R"("posturl":"http://www.postur.fo/",)"
      u8R"("languages":"fo")"
      "}");
  region_data.emplace("FR", "{"
      u8R"("fmt":"%O%n%N%n%A%n%Z %C %X",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"33380,34092,33506",)"
      u8R"("posturl":"http://www.laposte.fr/Particulier/Utiliser-nos-outils-pratiques/Outils-et-documents/Trouvez-un-code-postal",)"
      u8R"("languages":"fr")"
      "}");
  region_data.emplace("GA", "{"
      u8R"("languages":"fr")"
      "}");
  region_data.emplace("GB", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      u8R"("require":"ACZ",)"
      u8R"("locality_name_type":"post_town",)"
      u8R"("zipex":"EC1Y 8SY,GIR 0AA,M2 5BQ,M34 4AB,CR0 2YR,DN16 9AA,W1A 4ZZ,EC1A 1HQ,OX14 4PG,BS18 8HF,NR25 7HG,RH6 0NP,BH23 6AA,B6 5BA,SO23 9AP,PO1 3AX,BFPO 61",)"
      u8R"("posturl":"http://www.royalmail.com/postcode-finder",)"
      u8R"("languages":"en~cy~gd~ga")"
      "}");
  region_data.emplace("GD", "{"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("GE", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"0101",)"
      u8R"("posturl":"http://www.georgianpost.ge/index.php?page=10",)"
      u8R"("languages":"ka~ab~os")"
      "}");
  region_data.emplace("GF", "{"
      u8R"("fmt":"%O%n%N%n%A%n%Z %C %X",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"97300",)"
      u8R"("posturl":"http://www.laposte.fr/Particulier/Utiliser-nos-outils-pratiques/Outils-et-documents/Trouvez-un-code-postal",)"
      u8R"("languages":"fr")"
      "}");
  region_data.emplace("GG", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%nGUERNSEY%n%Z",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"GY1 1AA,GY2 2BT",)"
      u8R"("posturl":"http://www.guernseypost.com/postcode_finder/",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("GH", "{"
      u8R"("languages":"ak~en~ee~gaa")"
      "}");
  region_data.emplace("GI", "{"
      u8R"("fmt":"%N%n%O%n%A%nGIBRALTAR%n%Z",)"
      u8R"("require":"A",)"
      u8R"("zipex":"GX11 1AA",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("GL", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"3900,3950,3911",)"
      u8R"("languages":"kl")"
      "}");
  region_data.emplace("GM", "{"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("GN", "{"
      u8R"("fmt":"%N%n%O%n%Z %A %C",)"
      u8R"("zipex":"001,200,100",)"
      u8R"("languages":"fr")"
      "}");
  region_data.emplace("GP", "{"
      u8R"("fmt":"%O%n%N%n%A%n%Z %C %X",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"97100",)"
      u8R"("posturl":"http://www.laposte.fr/Particulier/Utiliser-nos-outils-pratiques/Outils-et-documents/Trouvez-un-code-postal",)"
      u8R"("languages":"fr")"
      "}");
  region_data.emplace("GQ", "{"
      u8R"("languages":"es~fr~pt")"
      "}");
  region_data.emplace("GR", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"151 24,151 10,101 88",)"
      u8R"("posturl":"http://www.elta.gr/findapostcode.aspx",)"
      u8R"("languages":"el")"
      "}");
  region_data.emplace("GS", "{"
      u8R"("fmt":"%N%n%O%n%A%n%n%C%n%Z",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"SIQQ 1ZZ")"
      "}");
  region_data.emplace("GT", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z- %C",)"
      u8R"("zipex":"09001,01501",)"
      u8R"("languages":"es~quc")"
      "}");
  region_data.emplace("GU", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      u8R"("require":"ACZ",)"
      u8R"("zip_name_type":"zip",)"
      u8R"("zipex":"96910,96931",)"
      u8R"("posturl":"http://zip4.usps.com/zip4/welcome.jsp",)"
      u8R"("languages":"en~ch")"
      "}");
  region_data.emplace("GW", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"1000,1011",)"
      u8R"("languages":"pt")"
      "}");
  region_data.emplace("GY", "{"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("HK", "{"
      u8R"("fmt":"%S%n%C%n%A%n%O%n%N",)"
      u8R"("lfmt":"%N%n%O%n%A%n%C%n%S",)"
      u8R"("require":"AS",)"
      u8R"("state_name_type":"area",)"
      u8R"("locality_name_type":"district",)"
      u8R"("languages":"zh-Hant~en")"
      "}");
  region_data.emplace("HM", "{"
      u8R"("fmt":"%O%n%N%n%A%n%C %S %Z",)"
      u8R"("zipex":"7050")"
      "}");
  region_data.emplace("HN", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C, %S%n%Z",)"
      u8R"("require":"ACS",)"
      u8R"("zipex":"31301",)"
      u8R"("languages":"es")"
      "}");
  region_data.emplace("HR", "{"
      u8R"("fmt":"%N%n%O%n%A%nHR-%Z %C",)"
      u8R"("zipex":"10000,21001,10002",)"
      u8R"("posturl":"http://www.posta.hr/default.aspx?pretpum",)"
      u8R"("languages":"hr~it")"
      "}");
  region_data.emplace("HT", "{"
      u8R"("fmt":"%N%n%O%n%A%nHT%Z %C",)"
      u8R"("zipex":"6120,5310,6110,8510",)"
      u8R"("languages":"ht~fr")"
      "}");
  region_data.emplace("HU", "{"
      u8R"("fmt":"%N%n%O%n%C%n%A%n%Z",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"1037,2380,1540",)"
      u8R"("posturl":"http://posta.hu/ugyfelszolgalat/iranyitoszam_kereso",)"
      u8R"("languages":"hu")"
      "}");
  region_data.emplace("ID", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%S %Z",)"
      u8R"("require":"AS",)"
      u8R"("zipex":"40115",)"
      u8R"("languages":"id")"
      "}");
  region_data.emplace("IE", "{"
      u8R"("fmt":"%N%n%O%n%A%n%D%n%C%n%S %Z",)"
      u8R"("zip_name_type":"eircode",)"
      u8R"("state_name_type":"county",)"
      u8R"("sublocality_name_type":"townland",)"
      u8R"("zipex":"A65 F4E2",)"
      u8R"("posturl":"https://finder.eircode.ie",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("IL", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      u8R"("zipex":"9614303",)"
      u8R"("posturl":"http://www.israelpost.co.il/zipcode.nsf/demozip?openform",)"
      u8R"("languages":"iw~ar")"
      "}");
  region_data.emplace("IM", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"IM2 1AA,IM99 1PS",)"
      u8R"("posturl":"http://www.gov.im/post/postal/fr_main.asp",)"
      u8R"("languages":"en~gv")"
      "}");
  region_data.emplace("IN", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z%n%S",)"
      u8R"("require":"ACSZ",)"
      u8R"("zip_name_type":"pin",)"
      u8R"("state_name_type":"state",)"
      u8R"("zipex":"110034,110001",)"
      u8R"("posturl":"https://www.indiapost.gov.in/vas/pages/FindPinCode.aspx",)"
      u8R"("languages":"en~hi")"
      "}");
  region_data.emplace("IO", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"BBND 1ZZ",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("IQ", "{"
      u8R"("fmt":"%O%n%N%n%A%n%C, %S%n%Z",)"
      u8R"("require":"ACS",)"
      u8R"("zipex":"31001",)"
      u8R"("languages":"ar~ckb~az-Arab")"
      "}");
  region_data.emplace("IR", "{"
      u8R"("fmt":"%O%n%N%n%S%n%C, %D%n%A%n%Z",)"
      u8R"("sublocality_name_type":"neighborhood",)"
      u8R"("zipex":"11936-12345",)"
      u8R"("languages":"fa")"
      "}");
  region_data.emplace("IS", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"320,121,220,110",)"
      u8R"("posturl":"http://www.postur.is/einstaklingar/posthus/postnumer/",)"
      u8R"("languages":"is")"
      "}");
  region_data.emplace("IT", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C %S",)"
      u8R"("require":"ACSZ",)"
      u8R"("zipex":"00144,47037,39049",)"
      u8R"("posturl":"http://www.poste.it/online/cercacap/",)"
      u8R"("languages":"it")"
      "}");
  region_data.emplace("JE", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%nJERSEY%n%Z",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"JE1 1AA,JE2 2BT",)"
      u8R"("posturl":"http://www.jerseypost.com/tools/postcode-address-finder/",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("JM", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%S %X",)"
      u8R"("require":"ACS",)"
      u8R"("state_name_type":"parish",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("JO", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      u8R"("zipex":"11937,11190",)"
      u8R"("languages":"ar")"
      "}");
  region_data.emplace("JP", "{"
      u8R"("fmt":"〒%Z%n%S%n%A%n%O%n%N",)"
      u8R"("lfmt":"%N%n%O%n%A, %S%n%Z",)"
      u8R"("require":"ASZ",)"
      u8R"("state_name_type":"prefecture",)"
      u8R"("zipex":"154-0023,350-1106,951-8073,112-0001,208-0032,231-0012",)"
      u8R"("posturl":"http://www.post.japanpost.jp/zipcode/",)"
      u8R"("languages":"ja")"
      "}");
  region_data.emplace("KE", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      u8R"("zipex":"20100,00100",)"
      u8R"("languages":"sw~en")"
      "}");
  region_data.emplace("KG", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"720001",)"
      u8R"("languages":"ky~ru")"
      "}");
  region_data.emplace("KH", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      u8R"("zipex":"12203,14206,12000",)"
      u8R"("languages":"km")"
      "}");
  region_data.emplace("KI", "{"
      u8R"("fmt":"%N%n%O%n%A%n%S%n%C",)"
      u8R"("state_name_type":"island",)"
      u8R"("languages":"en~gil")"
      "}");
  region_data.emplace("KM", "{"
      u8R"("languages":"ar~fr~zdj~wni")"
      "}");
  region_data.emplace("KN", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C, %S",)"
      u8R"("require":"ACS",)"
      u8R"("state_name_type":"island",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("KR", "{"
      u8R"("fmt":"%S %C%D%n%A%n%O%n%N%n%Z",)"
      u8R"("lfmt":"%N%n%O%n%A%n%D%n%C%n%S%n%Z",)"
      u8R"("require":"ACSZ",)"
      u8R"("state_name_type":"do_si",)"
      u8R"("sublocality_name_type":"district",)"
      u8R"("zipex":"03051",)"
      u8R"("posturl":"http://www.epost.go.kr/search/zipcode/search5.jsp",)"
      u8R"("languages":"ko")"
      "}");
  region_data.emplace("KW", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"54541,54551,54404,13009",)"
      u8R"("languages":"ar")"
      "}");
  region_data.emplace("KY", "{"
      u8R"("fmt":"%N%n%O%n%A%n%S %Z",)"
      u8R"("require":"AS",)"
      u8R"("state_name_type":"island",)"
      u8R"("zipex":"KY1-1100,KY1-1702,KY2-2101",)"
      u8R"("posturl":"http://www.caymanpost.gov.ky/",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("KZ", "{"
      u8R"("fmt":"%Z%n%S%n%C%n%A%n%O%n%N",)"
      u8R"("zipex":"040900,050012",)"
      u8R"("languages":"ru~kk")"
      "}");
  region_data.emplace("LA", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"01160,01000",)"
      u8R"("languages":"lo")"
      "}");
  region_data.emplace("LB", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      u8R"("zipex":"2038 3054,1107 2810,1000",)"
      u8R"("languages":"ar")"
      "}");
  region_data.emplace("LC", "{"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("LI", "{"
      u8R"("fmt":"%O%n%N%n%A%nFL-%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"9496,9491,9490,9485",)"
      u8R"("posturl":"http://www.post.ch/db/owa/pv_plz_pack/pr_main",)"
      u8R"("languages":"de~gsw")"
      "}");
  region_data.emplace("LK", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      u8R"("zipex":"20000,00100",)"
      u8R"("posturl":"http://www.slpost.gov.lk/",)"
      u8R"("languages":"si~ta")"
      "}");
  region_data.emplace("LR", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"1000",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("LS", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      u8R"("zipex":"100",)"
      u8R"("languages":"st~en")"
      "}");
  region_data.emplace("LT", "{"
      u8R"("fmt":"%O%n%N%n%A%nLT-%Z %C",)"
      u8R"("zipex":"04340,03500",)"
      u8R"("posturl":"http://www.post.lt/lt/?id=316",)"
      u8R"("languages":"lt")"
      "}");
  region_data.emplace("LU", "{"
      u8R"("fmt":"%O%n%N%n%A%nL-%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"4750,2998",)"
      u8R"("posturl":"https://www.post.lu/fr/grandes-entreprises/solutions-postales/rechercher-un-code-postal",)"
      u8R"("languages":"fr~lb~de")"
      "}");
  region_data.emplace("LV", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C, %Z",)"
      u8R"("zipex":"LV-1073,LV-1000",)"
      u8R"("posturl":"http://www.pasts.lv/lv/uzzinas/nodalas/",)"
      u8R"("languages":"lv")"
      "}");
  region_data.emplace("LY", "{"
      u8R"("languages":"ar")"
      "}");
  region_data.emplace("MA", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"53000,10000,20050,16052",)"
      u8R"("languages":"ar~fr~tzm")"
      "}");
  region_data.emplace("MC", "{"
      u8R"("fmt":"%N%n%O%n%A%nMC-%Z %C %X",)"
      u8R"("zipex":"98000,98020,98011,98001",)"
      u8R"("languages":"fr")"
      "}");
  region_data.emplace("MD", "{"
      u8R"("fmt":"%N%n%O%n%A%nMD-%Z %C",)"
      u8R"("zipex":"2012,2019",)"
      u8R"("languages":"ro")"
      "}");
  region_data.emplace("ME", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"81257,81258,81217,84314,85366",)"
      u8R"("languages":"sr-Latn")"
      "}");
  region_data.emplace("MF", "{"
      u8R"("fmt":"%O%n%N%n%A%n%Z %C %X",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"97100",)"
      u8R"("posturl":"http://www.laposte.fr/Particulier/Utiliser-nos-outils-pratiques/Outils-et-documents/Trouvez-un-code-postal",)"
      u8R"("languages":"fr")"
      "}");
  region_data.emplace("MG", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"501,101",)"
      u8R"("languages":"mg~fr~en")"
      "}");
  region_data.emplace("MH", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %S %Z",)"
      u8R"("require":"ACSZ",)"
      u8R"("zip_name_type":"zip",)"
      u8R"("state_name_type":"state",)"
      u8R"("zipex":"96960,96970",)"
      u8R"("posturl":"http://zip4.usps.com/zip4/welcome.jsp",)"
      u8R"("languages":"en~mh")"
      "}");
  region_data.emplace("MK", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"1314,1321,1443,1062",)"
      u8R"("languages":"mk~sq")"
      "}");
  region_data.emplace("ML", "{"
      u8R"("languages":"fr")"
      "}");
  region_data.emplace("MM", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C, %Z",)"
      u8R"("zipex":"11181",)"
      u8R"("languages":"my")"
      "}");
  region_data.emplace("MN", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%S %Z",)"
      u8R"("zipex":"65030,65270",)"
      u8R"("posturl":"http://www.zipcode.mn/",)"
      u8R"("languages":"mn")"
      "}");
  region_data.emplace("MO", "{"
      u8R"("fmt":"%A%n%O%n%N",)"
      u8R"("lfmt":"%N%n%O%n%A",)"
      u8R"("require":"A",)"
      u8R"("languages":"zh-Hant~pt")"
      "}");
  region_data.emplace("MP", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %S %Z",)"
      u8R"("require":"ACSZ",)"
      u8R"("zip_name_type":"zip",)"
      u8R"("state_name_type":"state",)"
      u8R"("zipex":"96950,96951,96952",)"
      u8R"("posturl":"http://zip4.usps.com/zip4/welcome.jsp",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("MQ", "{"
      u8R"("fmt":"%O%n%N%n%A%n%Z %C %X",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"97220",)"
      u8R"("posturl":"http://www.laposte.fr/Particulier/Utiliser-nos-outils-pratiques/Outils-et-documents/Trouvez-un-code-postal",)"
      u8R"("languages":"fr")"
      "}");
  region_data.emplace("MR", "{"
      u8R"("languages":"ar")"
      "}");
  region_data.emplace("MS", "{"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("MT", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      u8R"("zipex":"NXR 01,ZTN 05,GPO 01,BZN 1130,SPB 6031,VCT 1753",)"
      u8R"("posturl":"http://postcodes.maltapost.com/",)"
      u8R"("languages":"mt~en")"
      "}");
  region_data.emplace("MU", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z%n%C",)"
      u8R"("zipex":"42602",)"
      u8R"("languages":"en~fr")"
      "}");
  region_data.emplace("MV", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      u8R"("zipex":"20026",)"
      u8R"("posturl":"http://www.maldivespost.com/?lid=10",)"
      u8R"("languages":"dv")"
      "}");
  region_data.emplace("MW", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %X",)"
      u8R"("languages":"en~ny")"
      "}");
  region_data.emplace("MX", "{"
      u8R"("fmt":"%N%n%O%n%A%n%D%n%Z %C, %S",)"
      u8R"("require":"ACZ",)"
      u8R"("state_name_type":"state",)"
      u8R"("sublocality_name_type":"neighborhood",)"
      u8R"("zipex":"02860,77520,06082",)"
      u8R"("posturl":"http://www.correosdemexico.gob.mx/ServiciosLinea/Paginas/ccpostales.aspx",)"
      u8R"("languages":"es")"
      "}");
  region_data.emplace("MY", "{"
      u8R"("fmt":"%N%n%O%n%A%n%D%n%Z %C%n%S",)"
      u8R"("require":"ACZ",)"
      u8R"("state_name_type":"state",)"
      u8R"("sublocality_name_type":"village_township",)"
      u8R"("zipex":"43000,50754,88990,50670",)"
      u8R"("posturl":"http://www.pos.com.my",)"
      u8R"("languages":"ms")"
      "}");
  region_data.emplace("MZ", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"1102,1119,3212",)"
      u8R"("languages":"pt")"
      "}");
  region_data.emplace("NA", "{"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("NC", "{"
      u8R"("fmt":"%O%n%N%n%A%n%Z %C %X",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"98814,98800,98810",)"
      u8R"("posturl":"http://poste.opt.nc/index.php?option=com_content&view=article&id=80&Itemid=131",)"
      u8R"("languages":"fr")"
      "}");
  region_data.emplace("NE", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"8001",)"
      u8R"("languages":"fr")"
      "}");
  region_data.emplace("NF", "{"
      u8R"("fmt":"%O%n%N%n%A%n%C %S %Z",)"
      u8R"("zipex":"2899",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("NG", "{"
      u8R"("fmt":"%N%n%O%n%A%n%D%n%C %Z%n%S",)"
      u8R"("state_name_type":"state",)"
      u8R"("zipex":"930283,300001,931104",)"
      u8R"("posturl":"http://www.nigeriapostcodes.com/",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("NI", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z%n%C, %S",)"
      u8R"("state_name_type":"department",)"
      u8R"("zipex":"52000",)"
      u8R"("posturl":"http://www.correos.gob.ni/index.php/codigo-postal-2",)"
      u8R"("languages":"es")"
      "}");
  region_data.emplace("NL", "{"
      u8R"("fmt":"%O%n%N%n%A%n%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"1234 AB,2490 AA",)"
      u8R"("posturl":"http://www.postnl.nl/voorthuis/",)"
      u8R"("languages":"nl~fy")"
      "}");
  region_data.emplace("NO", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("locality_name_type":"post_town",)"
      u8R"("zipex":"0025,0107,6631",)"
      u8R"("posturl":"http://adressesok.posten.no/nb/postal_codes/search",)"
      u8R"("languages":"no~nn~se")"
      "}");
  region_data.emplace("NP", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      u8R"("zipex":"44601",)"
      u8R"("posturl":"http://www.gpo.gov.np/postalcode.aspx",)"
      u8R"("languages":"ne")"
      "}");
  region_data.emplace("NR", "{"
      u8R"("fmt":"%N%n%O%n%A%n%S",)"
      u8R"("require":"AS",)"
      u8R"("state_name_type":"district",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("NU", "{"
      u8R"("languages":"en~niu")"
      "}");
  region_data.emplace("NZ", "{"
      u8R"("fmt":"%N%n%O%n%A%n%D%n%C %Z",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"6001,6015,6332,8252,1030",)"
      u8R"("posturl":"http://www.nzpost.co.nz/Cultures/en-NZ/OnlineTools/PostCodeFinder/",)"
      u8R"("languages":"en~mi")"
      "}");
  region_data.emplace("OM", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z%n%C",)"
      u8R"("zipex":"133,112,111",)"
      u8R"("languages":"ar")"
      "}");
  region_data.emplace("PA", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%S",)"
      u8R"("languages":"es")"
      "}");
  region_data.emplace("PE", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z%n%S",)"
      u8R"("zipex":"LIMA 23,LIMA 42,CALLAO 2,02001",)"
      u8R"("posturl":"http://www.serpost.com.pe/cpostal/codigo",)"
      u8R"("languages":"es~qu")"
      "}");
  region_data.emplace("PF", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C %S",)"
      u8R"("require":"ACSZ",)"
      u8R"("state_name_type":"island",)"
      u8R"("zipex":"98709",)"
      u8R"("languages":"fr~ty")"
      "}");
  region_data.emplace("PG", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z %S",)"
      u8R"("require":"ACS",)"
      u8R"("zipex":"111",)"
      u8R"("languages":"tpi~en~ho")"
      "}");
  region_data.emplace("PH", "{"
      u8R"("fmt":"%N%n%O%n%A%n%D, %C%n%Z %S",)"
      u8R"("zipex":"1008,1050,1135,1207,2000,1000",)"
      u8R"("posturl":"http://www.philpost.gov.ph/",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("PK", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C-%Z",)"
      u8R"("zipex":"44000",)"
      u8R"("posturl":"http://www.pakpost.gov.pk/postcode/postcode.html",)"
      u8R"("languages":"ur~en")"
      "}");
  region_data.emplace("PL", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"00-950,05-470,48-300,32-015,00-940",)"
      u8R"("posturl":"http://kody.poczta-polska.pl/",)"
      u8R"("languages":"pl~de~csb~lt")"
      "}");
  region_data.emplace("PM", "{"
      u8R"("fmt":"%O%n%N%n%A%n%Z %C %X",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"97500",)"
      u8R"("languages":"fr")"
      "}");
  region_data.emplace("PN", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"PCRN 1ZZ",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("PR", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C PR %Z",)"
      u8R"("require":"ACZ",)"
      u8R"("zip_name_type":"zip",)"
      u8R"("zipex":"00930",)"
      u8R"("posturl":"http://zip4.usps.com/zip4/welcome.jsp",)"
      u8R"("languages":"es~en")"
      "}");
  region_data.emplace("PS", "{"
      u8R"("languages":"ar")"
      "}");
  region_data.emplace("PT", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"2725-079,1250-096,1201-950,2860-571,1208-148",)"
      u8R"("posturl":"http://www.ctt.pt/feapl_2/app/open/tools.jspx?tool=1",)"
      u8R"("languages":"pt")"
      "}");
  region_data.emplace("PW", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %S %Z",)"
      u8R"("require":"ACSZ",)"
      u8R"("zip_name_type":"zip",)"
      u8R"("state_name_type":"state",)"
      u8R"("zipex":"96940",)"
      u8R"("posturl":"http://zip4.usps.com/zip4/welcome.jsp",)"
      u8R"("languages":"pau~en")"
      "}");
  region_data.emplace("PY", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"1536,1538,1209",)"
      u8R"("languages":"gn~es")"
      "}");
  region_data.emplace("QA", "{"
      u8R"("languages":"ar")"
      "}");
  region_data.emplace("RE", "{"
      u8R"("fmt":"%O%n%N%n%A%n%Z %C %X",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"97400",)"
      u8R"("posturl":"http://www.laposte.fr/Particulier/Utiliser-nos-outils-pratiques/Outils-et-documents/Trouvez-un-code-postal",)"
      u8R"("languages":"fr")"
      "}");
  region_data.emplace("RO", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"060274,061357,200716",)"
      u8R"("posturl":"http://www.posta-romana.ro/zip_codes",)"
      u8R"("languages":"ro")"
      "}");
  region_data.emplace("RS", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"106314",)"
      u8R"("posturl":"http://www.posta.rs/struktura/lat/aplikacije/pronadji/nadji-postu.asp",)"
      u8R"("languages":"sr~sr-Latn~hu~ro~hr~sk~uk")"
      "}");
  region_data.emplace("RU", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%S%n%Z",)"
      u8R"("lfmt":"%N%n%O%n%A%n%C%n%S%n%Z",)"
      u8R"("require":"ACSZ",)"
      u8R"("state_name_type":"oblast",)"
      u8R"("zipex":"247112,103375,188300",)"
      u8R"("posturl":"http://info.russianpost.ru/servlet/department",)"
      u8R"("languages":"ru")"
      "}");
  region_data.emplace("RW", "{"
      u8R"("languages":"rw~en~fr")"
      "}");
  region_data.emplace("SA", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      u8R"("zipex":"11564,11187,11142",)"
      u8R"("languages":"ar")"
      "}");
  region_data.emplace("SB", "{"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("SC", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%S",)"
      u8R"("state_name_type":"island",)"
      u8R"("languages":"fr~en")"
      "}");
  region_data.emplace("SE", "{"
      u8R"("fmt":"%O%n%N%n%A%nSE-%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("locality_name_type":"post_town",)"
      u8R"("zipex":"11455,12345,10500",)"
      u8R"("posturl":"http://www.posten.se/sv/Kundservice/Sidor/Sok-postnummer-resultat.aspx",)"
      u8R"("languages":"sv~fi")"
      "}");
  region_data.emplace("SG", "{"
      u8R"("fmt":"%N%n%O%n%A%nSINGAPORE %Z",)"
      u8R"("require":"AZ",)"
      u8R"("zipex":"546080,308125,408600",)"
      u8R"("posturl":"https://www.singpost.com/find-postal-code",)"
      u8R"("languages":"en~zh~ms~ta")"
      "}");
  region_data.emplace("SH", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"STHL 1ZZ",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("SI", "{"
      u8R"("fmt":"%N%n%O%n%A%nSI-%Z %C",)"
      u8R"("zipex":"4000,1001,2500",)"
      u8R"("languages":"sl")"
      "}");
  region_data.emplace("SJ", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("locality_name_type":"post_town",)"
      u8R"("zipex":"9170",)"
      u8R"("posturl":"http://epab.posten.no/",)"
      u8R"("languages":"no")"
      "}");
  region_data.emplace("SK", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"010 01,023 14,972 48,921 01,975 99",)"
      u8R"("posturl":"http://psc.posta.sk",)"
      u8R"("languages":"sk")"
      "}");
  region_data.emplace("SL", "{"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("SM", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("require":"AZ",)"
      u8R"("zipex":"47890,47891,47895,47899",)"
      u8R"("posturl":"http://www.poste.it/online/cercacap/",)"
      u8R"("languages":"it")"
      "}");
  region_data.emplace("SN", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"12500,46024,16556,10000",)"
      u8R"("languages":"wo~fr~ff~srr~dyo~sav~mfv~bjt~snf~knf~bsc~mey~tnr")"
      "}");
  region_data.emplace("SO", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C, %S %Z",)"
      u8R"("require":"ACS",)"
      u8R"("zipex":"JH 09010,AD 11010",)"
      u8R"("languages":"so")"
      "}");
  region_data.emplace("SR", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%S",)"
      u8R"("languages":"nl")"
      "}");
  region_data.emplace("SS", "{"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("ST", "{"
      u8R"("languages":"pt")"
      "}");
  region_data.emplace("SV", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z-%C%n%S",)"
      u8R"("require":"ACS",)"
      u8R"("zipex":"CP 1101",)"
      u8R"("languages":"es")"
      "}");
  region_data.emplace("SX", "{"
      u8R"("languages":"en~nl")"
      "}");
  region_data.emplace("SZ", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      u8R"("zipex":"H100",)"
      u8R"("posturl":"http://www.sptc.co.sz/swazipost/codes/index.php",)"
      u8R"("languages":"en~ss")"
      "}");
  region_data.emplace("TA", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      u8R"("zipex":"TDCU 1ZZ",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("TC", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"TKCA 1ZZ",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("TD", "{"
      u8R"("languages":"fr~ar")"
      "}");
  region_data.emplace("TF", "{"
      u8R"("languages":"fr")"
      "}");
  region_data.emplace("TG", "{"
      u8R"("languages":"fr")"
      "}");
  region_data.emplace("TH", "{"
      u8R"("fmt":"%N%n%O%n%A%n%D %C%n%S %Z",)"
      u8R"("lfmt":"%N%n%O%n%A%n%D, %C%n%S %Z",)"
      u8R"("zipex":"10150,10210",)"
      u8R"("languages":"th")"
      "}");
  region_data.emplace("TJ", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"735450,734025",)"
      u8R"("languages":"tg")"
      "}");
  region_data.emplace("TK", "{"
      u8R"("languages":"en~tkl")"
      "}");
  region_data.emplace("TL", "{"
      u8R"("languages":"pt~tet")"
      "}");
  region_data.emplace("TM", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"744000",)"
      u8R"("languages":"tk")"
      "}");
  region_data.emplace("TN", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"1002,8129,3100,1030",)"
      u8R"("posturl":"http://www.poste.tn/codes.php",)"
      u8R"("languages":"ar~fr")"
      "}");
  region_data.emplace("TO", "{"
      u8R"("languages":"to~en")"
      "}");
  region_data.emplace("TR", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C/%S",)"
      u8R"("require":"ACZ",)"
      u8R"("locality_name_type":"district",)"
      u8R"("zipex":"01960,06101",)"
      u8R"("posturl":"http://postakodu.ptt.gov.tr/",)"
      u8R"("languages":"tr")"
      "}");
  region_data.emplace("TT", "{"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("TV", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%S",)"
      u8R"("state_name_type":"island",)"
      u8R"("languages":"tyv")"
      "}");
  region_data.emplace("TW", "{"
      u8R"("fmt":"%Z%n%S%C%n%A%n%O%n%N",)"
      u8R"("lfmt":"%N%n%O%n%A%n%C, %S %Z",)"
      u8R"("require":"ACSZ",)"
      u8R"("state_name_type":"county",)"
      u8R"("zipex":"104,106,10603,40867",)"
      u8R"("posturl":"http://www.post.gov.tw/post/internet/f_searchzone/index.jsp?ID=190102",)"
      u8R"("languages":"zh-Hant")"
      "}");
  region_data.emplace("TZ", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"6090,34413",)"
      u8R"("languages":"sw~en")"
      "}");
  region_data.emplace("UA", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%S%n%Z",)"
      u8R"("lfmt":"%N%n%O%n%A%n%C%n%S%n%Z",)"
      u8R"("require":"ACSZ",)"
      u8R"("state_name_type":"oblast",)"
      u8R"("zipex":"15432,01055,01001",)"
      u8R"("posturl":"http://services.ukrposhta.com/postindex_new/",)"
      u8R"("languages":"uk")"
      "}");
  region_data.emplace("UG", "{"
      u8R"("languages":"sw~en")"
      "}");
  region_data.emplace("UM", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %S %Z",)"
      u8R"("require":"ACS",)"
      u8R"("zip_name_type":"zip",)"
      u8R"("state_name_type":"state",)"
      u8R"("zipex":"96898",)"
      u8R"("posturl":"http://zip4.usps.com/zip4/welcome.jsp",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("US", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C, %S %Z",)"
      u8R"("require":"ACSZ",)"
      u8R"("zip_name_type":"zip",)"
      u8R"("state_name_type":"state",)"
      u8R"("zipex":"95014,22162-1010",)"
      u8R"("posturl":"https://tools.usps.com/go/ZipLookupAction!input.action",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("UY", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C %S",)"
      u8R"("zipex":"11600",)"
      u8R"("posturl":"http://www.correo.com.uy/index.asp?codPag=codPost&switchMapa=codPost",)"
      u8R"("languages":"es")"
      "}");
  region_data.emplace("UZ", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C%n%S",)"
      u8R"("zipex":"702100,700000",)"
      u8R"("posturl":"http://www.pochta.uz/ru/uslugi/indexsearch.html",)"
      u8R"("languages":"uz~uz-Cyrl")"
      "}");
  region_data.emplace("VA", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"00120",)"
      u8R"("languages":"it")"
      "}");
  region_data.emplace("VC", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z",)"
      u8R"("zipex":"VC0100,VC0110,VC0400",)"
      u8R"("posturl":"http://www.svgpost.gov.vc/?option=com_content&view=article&id=3&Itemid=16",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("VE", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %Z, %S",)"
      u8R"("require":"ACS",)"
      u8R"("state_name_type":"state",)"
      u8R"("zipex":"1010,3001,8011,1020",)"
      u8R"("posturl":"http://www.ipostel.gob.ve/index.php/oficinas-postales",)"
      u8R"("languages":"es")"
      "}");
  region_data.emplace("VG", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%Z",)"
      u8R"("require":"A",)"
      u8R"("zipex":"VG1110,VG1150,VG1160",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("VI", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C %S %Z",)"
      u8R"("require":"ACSZ",)"
      u8R"("zip_name_type":"zip",)"
      u8R"("state_name_type":"state",)"
      u8R"("zipex":"00802-1222,00850-9802",)"
      u8R"("posturl":"http://zip4.usps.com/zip4/welcome.jsp",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("VN", "{"
      u8R"("fmt":"%N%n%O%n%A%n%C%n%S %Z",)"
      u8R"("lfmt":"%N%n%O%n%A%n%C%n%S %Z",)"
      u8R"("zipex":"119415,136065,720344",)"
      u8R"("posturl":"http://postcode.vnpost.vn/services/search.aspx",)"
      u8R"("languages":"vi")"
      "}");
  region_data.emplace("VU", "{"
      u8R"("languages":"bi~en~fr")"
      "}");
  region_data.emplace("WF", "{"
      u8R"("fmt":"%O%n%N%n%A%n%Z %C %X",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"98600",)"
      u8R"("languages":"fr")"
      "}");
  region_data.emplace("WS", "{"
      u8R"("languages":"sm~en")"
      "}");
  region_data.emplace("XK", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"10000",)"
      u8R"("languages":"sq~sr~sr-Latn")"
      "}");
  region_data.emplace("YE", "{"
      u8R"("languages":"ar")"
      "}");
  region_data.emplace("YT", "{"
      u8R"("fmt":"%O%n%N%n%A%n%Z %C %X",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"97600",)"
      u8R"("languages":"fr")"
      "}");
  region_data.emplace("ZA", "{"
      u8R"("fmt":"%N%n%O%n%A%n%D%n%C%n%Z",)"
      u8R"("require":"ACZ",)"
      u8R"("zipex":"0083,1451,0001",)"
      u8R"("posturl":"https://www.postoffice.co.za/contactus/postalcode.html",)"
      u8R"("languages":"en~zu~xh~af~nso~tn~st~ts~ss~ve~nr")"
      "}");
  region_data.emplace("ZM", "{"
      u8R"("fmt":"%N%n%O%n%A%n%Z %C",)"
      u8R"("zipex":"50100,50101",)"
      u8R"("languages":"en")"
      "}");
  region_data.emplace("ZW", "{"
      u8R"("languages":"sn~en~nd")"
      "}");
  return region_data;
}

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

const std::map<std::string, std::string>& GetAllRegionData() {
  static const std::map<std::string, std::string> kRegionData(InitRegionData());
  return kRegionData;
}

struct SelectFirst {
  template <typename Pair>
  const typename Pair::first_type& operator()(const Pair& pair) const {
    return pair.first;
  }
};

std::vector<std::string> InitRegionCodes() {
  std::vector<std::string> region_codes(GetAllRegionData().size());
  std::transform(GetAllRegionData().begin(),
                 GetAllRegionData().end(),
                 region_codes.begin(),
                 SelectFirst());
  return region_codes;
}

const std::map<std::string, size_t> InitMaxLookupKeyDepth() {
  std::map<std::string, size_t> max_depth;
  for (const auto& pair : GetAllRegionData()) {
    std::vector<FormatElement> fields;
    // Here pair.second actually contains the entire JSON blob for this region,
    // and not only the format field, but it doesn't really matter when just
    // checking whether a particular formatting code (eg. "%C") is present, as
    // there isn't anything else in the JSON that erroneously could match a
    // formatting code.
    ParseFormatRule(pair.second, &fields);
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
    max_depth.emplace(pair.first, depth - 1);
  }
  return max_depth;
}

}  // namespace

// static
bool RegionDataConstants::IsSupported(const std::string& region_code) {
  static const std::set<std::string> kRegionCodes(GetRegionCodes().begin(),
                                                  GetRegionCodes().end());
  return kRegionCodes.find(region_code) != kRegionCodes.end();
}

// static
const std::vector<std::string>& RegionDataConstants::GetRegionCodes() {
  static const std::vector<std::string> kRegionCodes(InitRegionCodes());
  return kRegionCodes;
}

// static
const std::string& RegionDataConstants::GetRegionData(
    const std::string& region_code) {
  static const std::string kEmptyString;
  auto it = GetAllRegionData().find(region_code);
  return it != GetAllRegionData().end() ? it->second : kEmptyString;
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
