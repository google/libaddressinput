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
#include <libaddressinput/util/basictypes.h>

#include <algorithm>
#include <cstddef>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "address_field_util.h"
#include "format_element.h"
#include "lookup_key.h"

namespace i18n {
namespace addressinput {
namespace {

std::map<std::string, std::string> InitRegionData() {
  std::map<std::string, std::string> region_data;
  region_data.insert(std::make_pair("AC", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C%n%Z\","
      "\"zipex\":\"ASCN 1ZZ\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("AD", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"AD100,AD501,AD700\","
      "\"posturl\":\"http://www.correos.es/comun/CodigosPostales/1010_s-CodPostal.asp\?Provincia=\","
      "\"languages\":\"ca\""
      "}"));
  region_data.insert(std::make_pair("AE", "{"
      "\"fmt\":\"%N%n%O%n%A%n%S\","
      "\"lfmt\":\"%N%n%O%n%A%n%S\","
      "\"require\":\"AS\","
      "\"state_name_type\":\"emirate\","
      "\"languages\":\"ar\""
      "}"));
  region_data.insert(std::make_pair("AF", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C%n%Z\","
      "\"zipex\":\"1001,2601,3801\","
      "\"languages\":\"fa~ps~uz-Arab~tk~bal\""
      "}"));
  region_data.insert(std::make_pair("AG", "{"
      "\"require\":\"A\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("AI", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C%n%Z\","
      "\"zipex\":\"2640\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("AL", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z%n%C\","
      "\"zipex\":\"1001,1017,3501\","
      "\"languages\":\"sq\""
      "}"));
  region_data.insert(std::make_pair("AM", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z%n%C%n%S\","
      "\"lfmt\":\"%N%n%O%n%A%n%Z%n%C%n%S\","
      "\"zipex\":\"375010,0002,0010\","
      "\"languages\":\"hy\""
      "}"));
  region_data.insert(std::make_pair("AO", "{"
      "\"languages\":\"pt\""
      "}"));
  region_data.insert(std::make_pair("AQ", "{"
      "}"));
  region_data.insert(std::make_pair("AR", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C%n%S\","
      "\"zipex\":\"C1070AAM,C1000WAM,B1000TBU,X5187XAB\","
      "\"posturl\":\"http://www.correoargentino.com.ar/formularios/cpa\","
      "\"languages\":\"es\""
      "}"));
  region_data.insert(std::make_pair("AS", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C %S %Z\","
      "\"require\":\"ACSZ\","
      "\"zip_name_type\":\"zip\","
      "\"state_name_type\":\"state\","
      "\"zipex\":\"96799\","
      "\"posturl\":\"http://zip4.usps.com/zip4/welcome.jsp\","
      "\"languages\":\"sm~en\""
      "}"));
  region_data.insert(std::make_pair("AT", "{"
      "\"fmt\":\"%O%n%N%n%A%n%Z %C\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"1010,3741\","
      "\"posturl\":\"http://www.post.at/post_subsite_postleitzahlfinder.php\","
      "\"languages\":\"de~hr~sl~hu\""
      "}"));
  region_data.insert(std::make_pair("AU", "{"
      "\"fmt\":\"%O%n%N%n%A%n%C %S %Z\","
      "\"require\":\"ACSZ\","
      "\"state_name_type\":\"state\","
      "\"locality_name_type\":\"suburb\","
      "\"zipex\":\"2060,3171,6430,4000,4006,3001\","
      "\"posturl\":\"http://www1.auspost.com.au/postcodes/\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("AW", "{"
      "\"languages\":\"nl~pap\""
      "}"));
  region_data.insert(std::make_pair("AX", "{"
      "\"fmt\":\"%O%n%N%n%A%nAX-%Z %C%n\\u00c5LAND\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"22150,22550,22240,22710,22270,22730,22430\","
      "\"posturl\":\"http://www.posten.ax/department.con\?iPage=123\","
      "\"languages\":\"sv\""
      "}"));
  region_data.insert(std::make_pair("AZ", "{"
      "\"fmt\":\"%N%n%O%n%A%nAZ %Z %C\","
      "\"zipex\":\"1000\","
      "\"languages\":\"az~az-Cyrl\""
      "}"));
  region_data.insert(std::make_pair("BA", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"71000\","
      "\"languages\":\"bs~bs-Cyrl~hr~sr~sr-Latn\""
      "}"));
  region_data.insert(std::make_pair("BB", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C, %S %Z\","
      "\"state_name_type\":\"parish\","
      "\"zipex\":\"BB23026,BB22025\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("BD", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C - %Z\","
      "\"zipex\":\"1340,1000\","
      "\"posturl\":\"http://www.bangladeshpost.gov.bd/PostCode.asp\","
      "\"languages\":\"bn\""
      "}"));
  region_data.insert(std::make_pair("BE", "{"
      "\"fmt\":\"%O%n%N%n%A%n%Z %C\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"4000,1000\","
      "\"posturl\":\"http://www.post.be/site/nl/residential/customerservice/search/postal_codes.html\","
      "\"languages\":\"nl~fr~de\""
      "}"));
  region_data.insert(std::make_pair("BF", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C %X\","
      "\"languages\":\"fr\""
      "}"));
  region_data.insert(std::make_pair("BG", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"1000,1700\","
      "\"posturl\":\"http://www.bgpost.bg/\?cid=5\","
      "\"languages\":\"bg\""
      "}"));
  region_data.insert(std::make_pair("BH", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C %Z\","
      "\"zipex\":\"317\","
      "\"languages\":\"ar\""
      "}"));
  region_data.insert(std::make_pair("BI", "{"
      "\"languages\":\"rn~fr~en\""
      "}"));
  region_data.insert(std::make_pair("BJ", "{"
      "\"languages\":\"fr\""
      "}"));
  region_data.insert(std::make_pair("BL", "{"
      "\"fmt\":\"%O%n%N%n%A%n%Z %C %X\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"97100\","
      "\"posturl\":\"http://www.laposte.fr/Particulier/Utiliser-nos-outils-pratiques/Outils-et-documents/Trouvez-un-code-postal\","
      "\"languages\":\"fr\""
      "}"));
  region_data.insert(std::make_pair("BM", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C %Z\","
      "\"zipex\":\"FL 07,HM GX,HM 12\","
      "\"posturl\":\"http://www.landvaluation.bm/\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("BN", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C %Z\","
      "\"zipex\":\"BT2328,KA1131,BA1511\","
      "\"posturl\":\"http://www.post.gov.bn/SitePages/postcodes.aspx\","
      "\"languages\":\"ms~ms-Arab\""
      "}"));
  region_data.insert(std::make_pair("BO", "{"
      "\"languages\":\"es~qu~ay\""
      "}"));
  region_data.insert(std::make_pair("BQ", "{"
      "\"languages\":\"nl\""
      "}"));
  region_data.insert(std::make_pair("BR", "{"
      "\"fmt\":\"%O%n%N%n%A%n%D%n%C-%S%n%Z\","
      "\"require\":\"ASCZ\","
      "\"state_name_type\":\"state\","
      "\"sublocality_name_type\":\"neighborhood\","
      "\"zipex\":\"40301-110,70002-900\","
      "\"posturl\":\"http://www.buscacep.correios.com.br/\","
      "\"languages\":\"pt\""
      "}"));
  region_data.insert(std::make_pair("BS", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C, %S\","
      "\"state_name_type\":\"island\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("BT", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C %Z\","
      "\"zipex\":\"11001,31101,35003\","
      "\"posturl\":\"http://www.bhutanpost.bt/searchpostcode.php\","
      "\"languages\":\"dz\""
      "}"));
  region_data.insert(std::make_pair("BV", "{"
      "}"));
  region_data.insert(std::make_pair("BW", "{"
      "\"languages\":\"en~tn\""
      "}"));
  region_data.insert(std::make_pair("BY", "{"
      "\"fmt\":\"%S%n%Z %C%n%A%n%O%n%N\","
      "\"zipex\":\"223016,225860,220050\","
      "\"posturl\":\"http://ex.belpost.by/addressbook/\","
      "\"languages\":\"be~ru\""
      "}"));
  region_data.insert(std::make_pair("BZ", "{"
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("CA", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C %S %Z\","
      "\"require\":\"ACSZ\","
      "\"zipex\":\"H3Z 2Y7,V8X 3X4,T0L 1K0,T0H 1A0,K1A 0B1\","
      "\"posturl\":\"https://www.canadapost.ca/cpo/mc/personal/postalcode/fpc.jsf\","
      "\"languages\":\"en~fr\""
      "}"));
  region_data.insert(std::make_pair("CC", "{"
      "\"fmt\":\"%O%n%N%n%A%n%C %S %Z\","
      "\"zipex\":\"6799\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("CD", "{"
      "\"languages\":\"sw~lua~fr~ln~kg\""
      "}"));
  region_data.insert(std::make_pair("CF", "{"
      "\"languages\":\"fr~sg\""
      "}"));
  region_data.insert(std::make_pair("CG", "{"
      "\"languages\":\"fr\""
      "}"));
  region_data.insert(std::make_pair("CH", "{"
      "\"fmt\":\"%O%n%N%n%A%nCH-%Z %C\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"2544,1211,1556,3030\","
      "\"posturl\":\"http://www.post.ch/db/owa/pv_plz_pack/pr_main\","
      "\"languages\":\"de~gsw~fr~it~rm\""
      "}"));
  region_data.insert(std::make_pair("CI", "{"
      "\"fmt\":\"%N%n%O%n%X %A %C %X\","
      "\"languages\":\"fr\""
      "}"));
  region_data.insert(std::make_pair("CK", "{"
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("CL", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C%n%S\","
      "\"zipex\":\"8340457,8720019,1230000,8329100\","
      "\"posturl\":\"http://www.correos.cl/SitePages/home.aspx\","
      "\"languages\":\"es\""
      "}"));
  region_data.insert(std::make_pair("CM", "{"
      "\"languages\":\"fr~en\""
      "}"));
  region_data.insert(std::make_pair("CN", "{"
      "\"fmt\":\"%Z%n%S%C%D%n%A%n%O%n%N\","
      "\"lfmt\":\"%N%n%O%n%A%n%D%n%C%n%S, %Z\","
      "\"require\":\"ACSZ\","
      "\"sublocality_name_type\":\"district\","
      "\"zipex\":\"266033,317204,100096,100808\","
      "\"posturl\":\"http://www.ems.com.cn/serviceguide/you_bian_cha_xun.html\","
      "\"languages\":\"zh\""
      "}"));
  region_data.insert(std::make_pair("CO", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C, %S, %Z\","
      "\"require\":\"AS\","
      "\"state_name_type\":\"department\","
      "\"zipex\":\"111221,130001,760011\","
      "\"posturl\":\"http://www.codigopostal.gov.co/\","
      "\"languages\":\"es\""
      "}"));
  region_data.insert(std::make_pair("CR", "{"
      "\"fmt\":\"%N%n%O%n%A%n%S, %C%n%Z\","
      "\"require\":\"ACS\","
      "\"zipex\":\"1000,2010,1001\","
      "\"posturl\":\"https://www.correos.go.cr/nosotros/codigopostal/busqueda.html\","
      "\"languages\":\"es\""
      "}"));
  region_data.insert(std::make_pair("CV", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C%n%S\","
      "\"state_name_type\":\"island\","
      "\"zipex\":\"7600\","
      "\"languages\":\"pt\""
      "}"));
  region_data.insert(std::make_pair("CW", "{"
      "\"languages\":\"pap~nl\""
      "}"));
  region_data.insert(std::make_pair("CX", "{"
      "\"fmt\":\"%O%n%N%n%A%n%C %S %Z\","
      "\"zipex\":\"6798\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("CY", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"2008,3304,1900\","
      "\"languages\":\"el~tr\""
      "}"));
  region_data.insert(std::make_pair("CZ", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"100 00,251 66,530 87,110 00,225 99\","
      "\"posturl\":\"http://psc.ceskaposta.cz/CleanForm.action\","
      "\"languages\":\"cs\""
      "}"));
  region_data.insert(std::make_pair("DE", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"26133,53225\","
      "\"posturl\":\"http://www.postdirekt.de/plzserver/\","
      "\"languages\":\"de\""
      "}"));
  region_data.insert(std::make_pair("DJ", "{"
      "\"languages\":\"ar~fr\""
      "}"));
  region_data.insert(std::make_pair("DK", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"8660,1566\","
      "\"posturl\":\"http://www.postdanmark.dk/da/Privat/Kundeservice/postnummerkort/Sider/Find-postnummer.aspx\","
      "\"languages\":\"da~de~kl\""
      "}"));
  region_data.insert(std::make_pair("DM", "{"
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("DO", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"11903,10101\","
      "\"posturl\":\"http://inposdom.gob.do/codigo-postal/\","
      "\"languages\":\"es\""
      "}"));
  region_data.insert(std::make_pair("DZ", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"40304,16027\","
      "\"languages\":\"ar~fr\""
      "}"));
  region_data.insert(std::make_pair("EC", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z%n%C\","
      "\"zipex\":\"090105,092301\","
      "\"posturl\":\"http://www.codigopostal.gob.ec/\","
      "\"languages\":\"es~qu\""
      "}"));
  region_data.insert(std::make_pair("EE", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"69501,11212\","
      "\"posturl\":\"https://www.omniva.ee/era/sihtnumbrite_otsing\","
      "\"languages\":\"et\""
      "}"));
  region_data.insert(std::make_pair("EG", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C%n%S%n%Z\","
      "\"lfmt\":\"%N%n%O%n%A%n%C%n%S%n%Z\","
      "\"zipex\":\"12411,11599\","
      "\"languages\":\"ar\""
      "}"));
  region_data.insert(std::make_pair("EH", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"70000,72000\","
      "\"languages\":\"ar\""
      "}"));
  region_data.insert(std::make_pair("ER", "{"
      "\"languages\":\"ti~en~ar\""
      "}"));
  region_data.insert(std::make_pair("ES", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C %S\","
      "\"require\":\"ACSZ\","
      "\"zipex\":\"28039,28300,28070\","
      "\"posturl\":\"http://www.correos.es/contenido/13-MenuRec2/04-MenuRec24/1010_s-CodPostal.asp\","
      "\"languages\":\"es~ca~gl~eu\""
      "}"));
  region_data.insert(std::make_pair("ET", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"1000\","
      "\"languages\":\"am\""
      "}"));
  region_data.insert(std::make_pair("FI", "{"
      "\"fmt\":\"%O%n%N%n%A%nFI-%Z %C\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"00550,00011\","
      "\"posturl\":\"http://www.verkkoposti.com/e3/postinumeroluettelo\","
      "\"languages\":\"fi~sv\""
      "}"));
  region_data.insert(std::make_pair("FJ", "{"
      "\"languages\":\"en~hif~fj\""
      "}"));
  region_data.insert(std::make_pair("FK", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C%n%Z\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"FIQQ 1ZZ\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("FM", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C %S %Z\","
      "\"require\":\"ACSZ\","
      "\"zip_name_type\":\"zip\","
      "\"state_name_type\":\"state\","
      "\"zipex\":\"96941,96944\","
      "\"posturl\":\"http://zip4.usps.com/zip4/welcome.jsp\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("FO", "{"
      "\"fmt\":\"%N%n%O%n%A%nFO%Z %C\","
      "\"zipex\":\"100\","
      "\"posturl\":\"http://www.postur.fo/\","
      "\"languages\":\"fo\""
      "}"));
  region_data.insert(std::make_pair("FR", "{"
      "\"fmt\":\"%O%n%N%n%A%n%Z %C %X\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"33380,34092,33506\","
      "\"posturl\":\"http://www.laposte.fr/Particulier/Utiliser-nos-outils-pratiques/Outils-et-documents/Trouvez-un-code-postal\","
      "\"languages\":\"fr\""
      "}"));
  region_data.insert(std::make_pair("GA", "{"
      "\"languages\":\"fr\""
      "}"));
  region_data.insert(std::make_pair("GB", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C%n%Z\","
      "\"require\":\"ACZ\","
      "\"locality_name_type\":\"post_town\","
      "\"zipex\":\"EC1Y 8SY,GIR 0AA,M2 5BQ,M34 4AB,CR0 2YR,DN16 9AA,W1A 4ZZ,EC1A 1HQ,OX14 4PG,BS18 8HF,NR25 7HG,RH6 0NP,BH23 6AA,B6 5BA,SO23 9AP,PO1 3AX,BFPO 61\","
      "\"posturl\":\"http://www.royalmail.com/postcode-finder\","
      "\"languages\":\"en~cy~gd~ga\""
      "}"));
  region_data.insert(std::make_pair("GD", "{"
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("GE", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"0101\","
      "\"posturl\":\"http://www.georgianpost.ge/index.php\?page=10\","
      "\"languages\":\"ka~ab~os\""
      "}"));
  region_data.insert(std::make_pair("GF", "{"
      "\"fmt\":\"%O%n%N%n%A%n%Z %C %X\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"97300\","
      "\"posturl\":\"http://www.laposte.fr/Particulier/Utiliser-nos-outils-pratiques/Outils-et-documents/Trouvez-un-code-postal\","
      "\"languages\":\"fr\""
      "}"));
  region_data.insert(std::make_pair("GG", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C%nGUERNSEY%n%Z\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"GY1 1AA,GY2 2BT\","
      "\"posturl\":\"http://www.guernseypost.com/postcode_finder/\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("GH", "{"
      "\"languages\":\"ak~en~ee~gaa\""
      "}"));
  region_data.insert(std::make_pair("GI", "{"
      "\"fmt\":\"%N%n%O%n%A%nGIBRALTAR%n%Z\","
      "\"require\":\"A\","
      "\"zipex\":\"GX11 1AA\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("GL", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"3900,3950,3911\","
      "\"languages\":\"kl\""
      "}"));
  region_data.insert(std::make_pair("GM", "{"
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("GN", "{"
      "\"fmt\":\"%N%n%O%n%Z %A %C\","
      "\"zipex\":\"001,200,100\","
      "\"languages\":\"fr\""
      "}"));
  region_data.insert(std::make_pair("GP", "{"
      "\"fmt\":\"%O%n%N%n%A%n%Z %C %X\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"97100\","
      "\"posturl\":\"http://www.laposte.fr/Particulier/Utiliser-nos-outils-pratiques/Outils-et-documents/Trouvez-un-code-postal\","
      "\"languages\":\"fr\""
      "}"));
  region_data.insert(std::make_pair("GQ", "{"
      "\"languages\":\"es~fr~pt\""
      "}"));
  region_data.insert(std::make_pair("GR", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"151 24,151 10,101 88\","
      "\"posturl\":\"http://www.elta.gr/findapostcode.aspx\","
      "\"languages\":\"el\""
      "}"));
  region_data.insert(std::make_pair("GS", "{"
      "\"fmt\":\"%N%n%O%n%A%n%n%C%n%Z\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"SIQQ 1ZZ\""
      "}"));
  region_data.insert(std::make_pair("GT", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z- %C\","
      "\"zipex\":\"09001,01501\","
      "\"languages\":\"es~quc\""
      "}"));
  region_data.insert(std::make_pair("GU", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C %Z\","
      "\"require\":\"ACZ\","
      "\"zip_name_type\":\"zip\","
      "\"zipex\":\"96910,96931\","
      "\"posturl\":\"http://zip4.usps.com/zip4/welcome.jsp\","
      "\"languages\":\"en~ch\""
      "}"));
  region_data.insert(std::make_pair("GW", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"1000,1011\","
      "\"languages\":\"pt\""
      "}"));
  region_data.insert(std::make_pair("GY", "{"
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("HK", "{"
      "\"fmt\":\"%S%n%C%n%A%n%O%n%N\","
      "\"lfmt\":\"%N%n%O%n%A%n%C%n%S\","
      "\"require\":\"AS\","
      "\"state_name_type\":\"area\","
      "\"locality_name_type\":\"district\","
      "\"languages\":\"zh-Hant~en\""
      "}"));
  region_data.insert(std::make_pair("HM", "{"
      "\"fmt\":\"%O%n%N%n%A%n%C %S %Z\","
      "\"zipex\":\"7050\""
      "}"));
  region_data.insert(std::make_pair("HN", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C, %S%n%Z\","
      "\"require\":\"ACS\","
      "\"zipex\":\"31301\","
      "\"languages\":\"es\""
      "}"));
  region_data.insert(std::make_pair("HR", "{"
      "\"fmt\":\"%N%n%O%n%A%nHR-%Z %C\","
      "\"zipex\":\"10000,21001,10002\","
      "\"posturl\":\"http://www.posta.hr/default.aspx\?pretpum\","
      "\"languages\":\"hr~it\""
      "}"));
  region_data.insert(std::make_pair("HT", "{"
      "\"fmt\":\"%N%n%O%n%A%nHT%Z %C\","
      "\"zipex\":\"6120,5310,6110,8510\","
      "\"languages\":\"ht~fr\""
      "}"));
  region_data.insert(std::make_pair("HU", "{"
      "\"fmt\":\"%N%n%O%n%C%n%A%n%Z\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"1037,2380,1540\","
      "\"posturl\":\"http://posta.hu/ugyfelszolgalat/iranyitoszam_kereso\","
      "\"languages\":\"hu\""
      "}"));
  region_data.insert(std::make_pair("ID", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C%n%S %Z\","
      "\"require\":\"AS\","
      "\"zipex\":\"40115\","
      "\"languages\":\"id\""
      "}"));
  region_data.insert(std::make_pair("IE", "{"
      "\"fmt\":\"%N%n%O%n%A%n%D%n%C%n%S %Z\","
      "\"zip_name_type\":\"eircode\","
      "\"state_name_type\":\"county\","
      "\"sublocality_name_type\":\"townland\","
      "\"zipex\":\"A65 F4E2\","
      "\"posturl\":\"https://finder.eircode.ie\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("IL", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C %Z\","
      "\"zipex\":\"9614303\","
      "\"posturl\":\"http://www.israelpost.co.il/zipcode.nsf/demozip\?openform\","
      "\"languages\":\"iw~ar\""
      "}"));
  region_data.insert(std::make_pair("IM", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C%n%Z\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"IM2 1AA,IM99 1PS\","
      "\"posturl\":\"http://www.gov.im/post/postal/fr_main.asp\","
      "\"languages\":\"en~gv\""
      "}"));
  region_data.insert(std::make_pair("IN", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C %Z%n%S\","
      "\"require\":\"ACSZ\","
      "\"zip_name_type\":\"pin\","
      "\"state_name_type\":\"state\","
      "\"zipex\":\"110034,110001\","
      "\"posturl\":\"https://www.indiapost.gov.in/vas/pages/FindPinCode.aspx\","
      "\"languages\":\"en~hi\""
      "}"));
  region_data.insert(std::make_pair("IO", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C%n%Z\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"BBND 1ZZ\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("IQ", "{"
      "\"fmt\":\"%O%n%N%n%A%n%C, %S%n%Z\","
      "\"require\":\"ACS\","
      "\"zipex\":\"31001\","
      "\"languages\":\"ar~ckb~az-Arab\""
      "}"));
  region_data.insert(std::make_pair("IR", "{"
      "\"fmt\":\"%O%n%N%n%S%n%C, %D%n%A%n%Z\","
      "\"sublocality_name_type\":\"neighborhood\","
      "\"zipex\":\"11936-12345\","
      "\"languages\":\"fa\""
      "}"));
  region_data.insert(std::make_pair("IS", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"320,121,220,110\","
      "\"posturl\":\"http://www.postur.is/einstaklingar/posthus/postnumer/\","
      "\"languages\":\"is\""
      "}"));
  region_data.insert(std::make_pair("IT", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C %S\","
      "\"require\":\"ACSZ\","
      "\"zipex\":\"00144,47037,39049\","
      "\"posturl\":\"http://www.poste.it/online/cercacap/\","
      "\"languages\":\"it\""
      "}"));
  region_data.insert(std::make_pair("JE", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C%nJERSEY%n%Z\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"JE1 1AA,JE2 2BT\","
      "\"posturl\":\"http://www.jerseypost.com/tools/postcode-address-finder/\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("JM", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C%n%S %X\","
      "\"require\":\"ACS\","
      "\"state_name_type\":\"parish\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("JO", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C %Z\","
      "\"zipex\":\"11937,11190\","
      "\"languages\":\"ar\""
      "}"));
  region_data.insert(std::make_pair("JP", "{"
      "\"fmt\":\"\\u3012%Z%n%S%C%n%A%n%O%n%N\","
      "\"lfmt\":\"%N%n%O%n%A%n%C, %S%n%Z\","
      "\"require\":\"ACSZ\","
      "\"state_name_type\":\"prefecture\","
      "\"zipex\":\"154-0023,350-1106,951-8073,112-0001,208-0032,231-0012\","
      "\"posturl\":\"http://search.post.japanpost.jp/zipcode/\","
      "\"languages\":\"ja\""
      "}"));
  region_data.insert(std::make_pair("KE", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C%n%Z\","
      "\"zipex\":\"20100,00100\","
      "\"languages\":\"sw~en\""
      "}"));
  region_data.insert(std::make_pair("KG", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"720001\","
      "\"languages\":\"ky~ru\""
      "}"));
  region_data.insert(std::make_pair("KH", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C %Z\","
      "\"zipex\":\"12203,14206,12000\","
      "\"languages\":\"km\""
      "}"));
  region_data.insert(std::make_pair("KI", "{"
      "\"fmt\":\"%N%n%O%n%A%n%S%n%C\","
      "\"state_name_type\":\"island\","
      "\"languages\":\"en~gil\""
      "}"));
  region_data.insert(std::make_pair("KM", "{"
      "\"languages\":\"ar~fr~zdj~wni\""
      "}"));
  region_data.insert(std::make_pair("KN", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C, %S\","
      "\"require\":\"ACS\","
      "\"state_name_type\":\"island\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("KR", "{"
      "\"fmt\":\"%S %C%D%n%A%n%O%n%N%n%Z\","
      "\"lfmt\":\"%N%n%O%n%A%n%D%n%C%n%S%n%Z\","
      "\"require\":\"ACSZ\","
      "\"state_name_type\":\"do_si\","
      "\"sublocality_name_type\":\"district\","
      "\"zipex\":\"03051\","
      "\"posturl\":\"http://www.epost.go.kr/search/zipcode/search5.jsp\","
      "\"languages\":\"ko\""
      "}"));
  region_data.insert(std::make_pair("KW", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"54541,54551,54404,13009\","
      "\"languages\":\"ar\""
      "}"));
  region_data.insert(std::make_pair("KY", "{"
      "\"fmt\":\"%N%n%O%n%A%n%S %Z\","
      "\"require\":\"AS\","
      "\"state_name_type\":\"island\","
      "\"zipex\":\"KY1-1100,KY1-1702,KY2-2101\","
      "\"posturl\":\"http://www.caymanpost.gov.ky/\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("KZ", "{"
      "\"fmt\":\"%Z%n%S%n%C%n%A%n%O%n%N\","
      "\"zipex\":\"040900,050012\","
      "\"languages\":\"ru~kk\""
      "}"));
  region_data.insert(std::make_pair("LA", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"01160,01000\","
      "\"languages\":\"lo\""
      "}"));
  region_data.insert(std::make_pair("LB", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C %Z\","
      "\"zipex\":\"2038 3054,1107 2810,1000\","
      "\"languages\":\"ar\""
      "}"));
  region_data.insert(std::make_pair("LC", "{"
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("LI", "{"
      "\"fmt\":\"%O%n%N%n%A%nFL-%Z %C\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"9496,9491,9490,9485\","
      "\"posturl\":\"http://www.post.ch/db/owa/pv_plz_pack/pr_main\","
      "\"languages\":\"de~gsw\""
      "}"));
  region_data.insert(std::make_pair("LK", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C%n%Z\","
      "\"zipex\":\"20000,00100\","
      "\"posturl\":\"http://www.slpost.gov.lk/\","
      "\"languages\":\"si~ta\""
      "}"));
  region_data.insert(std::make_pair("LR", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"1000\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("LS", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C %Z\","
      "\"zipex\":\"100\","
      "\"languages\":\"st~en\""
      "}"));
  region_data.insert(std::make_pair("LT", "{"
      "\"fmt\":\"%O%n%N%n%A%nLT-%Z %C\","
      "\"zipex\":\"04340,03500\","
      "\"posturl\":\"http://www.post.lt/lt/\?id=316\","
      "\"languages\":\"lt\""
      "}"));
  region_data.insert(std::make_pair("LU", "{"
      "\"fmt\":\"%O%n%N%n%A%nL-%Z %C\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"4750,2998\","
      "\"posturl\":\"https://www.post.lu/fr/grandes-entreprises/solutions-postales/rechercher-un-code-postal\","
      "\"languages\":\"fr~lb~de\""
      "}"));
  region_data.insert(std::make_pair("LV", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C, %Z\","
      "\"zipex\":\"LV-1073,LV-1000\","
      "\"posturl\":\"http://www.pasts.lv/lv/uzzinas/nodalas/\","
      "\"languages\":\"lv\""
      "}"));
  region_data.insert(std::make_pair("LY", "{"
      "\"languages\":\"ar\""
      "}"));
  region_data.insert(std::make_pair("MA", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"53000,10000,20050,16052\","
      "\"languages\":\"ar~fr~tzm\""
      "}"));
  region_data.insert(std::make_pair("MC", "{"
      "\"fmt\":\"%N%n%O%n%A%nMC-%Z %C %X\","
      "\"zipex\":\"98000,98020,98011,98001\","
      "\"languages\":\"fr\""
      "}"));
  region_data.insert(std::make_pair("MD", "{"
      "\"fmt\":\"%N%n%O%n%A%nMD-%Z %C\","
      "\"zipex\":\"2012,2019\","
      "\"languages\":\"ro\""
      "}"));
  region_data.insert(std::make_pair("ME", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"81257,81258,81217,84314,85366\","
      "\"languages\":\"sr-Latn\""
      "}"));
  region_data.insert(std::make_pair("MF", "{"
      "\"fmt\":\"%O%n%N%n%A%n%Z %C %X\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"97100\","
      "\"posturl\":\"http://www.laposte.fr/Particulier/Utiliser-nos-outils-pratiques/Outils-et-documents/Trouvez-un-code-postal\","
      "\"languages\":\"fr\""
      "}"));
  region_data.insert(std::make_pair("MG", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"501,101\","
      "\"languages\":\"mg~fr~en\""
      "}"));
  region_data.insert(std::make_pair("MH", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C %S %Z\","
      "\"require\":\"ACSZ\","
      "\"zip_name_type\":\"zip\","
      "\"state_name_type\":\"state\","
      "\"zipex\":\"96960,96970\","
      "\"posturl\":\"http://zip4.usps.com/zip4/welcome.jsp\","
      "\"languages\":\"en~mh\""
      "}"));
  region_data.insert(std::make_pair("MK", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"1314,1321,1443,1062\","
      "\"languages\":\"mk~sq\""
      "}"));
  region_data.insert(std::make_pair("ML", "{"
      "\"languages\":\"fr\""
      "}"));
  region_data.insert(std::make_pair("MM", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C, %Z\","
      "\"zipex\":\"11181\","
      "\"languages\":\"my\""
      "}"));
  region_data.insert(std::make_pair("MN", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C%n%S %Z\","
      "\"zipex\":\"65030,65270\","
      "\"posturl\":\"http://www.zipcode.mn/\","
      "\"languages\":\"mn\""
      "}"));
  region_data.insert(std::make_pair("MO", "{"
      "\"fmt\":\"%A%n%O%n%N\","
      "\"lfmt\":\"%N%n%O%n%A\","
      "\"require\":\"A\","
      "\"languages\":\"zh-Hant~pt\""
      "}"));
  region_data.insert(std::make_pair("MP", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C %S %Z\","
      "\"require\":\"ACSZ\","
      "\"zip_name_type\":\"zip\","
      "\"state_name_type\":\"state\","
      "\"zipex\":\"96950,96951,96952\","
      "\"posturl\":\"http://zip4.usps.com/zip4/welcome.jsp\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("MQ", "{"
      "\"fmt\":\"%O%n%N%n%A%n%Z %C %X\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"97220\","
      "\"posturl\":\"http://www.laposte.fr/Particulier/Utiliser-nos-outils-pratiques/Outils-et-documents/Trouvez-un-code-postal\","
      "\"languages\":\"fr\""
      "}"));
  region_data.insert(std::make_pair("MR", "{"
      "\"languages\":\"ar\""
      "}"));
  region_data.insert(std::make_pair("MS", "{"
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("MT", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C %Z\","
      "\"zipex\":\"NXR 01,ZTN 05,GPO 01,BZN 1130,SPB 6031,VCT 1753\","
      "\"posturl\":\"http://postcodes.maltapost.com/\","
      "\"languages\":\"mt~en\""
      "}"));
  region_data.insert(std::make_pair("MU", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z%n%C\","
      "\"zipex\":\"42602\","
      "\"languages\":\"en~fr\""
      "}"));
  region_data.insert(std::make_pair("MV", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C %Z\","
      "\"zipex\":\"20026\","
      "\"posturl\":\"http://www.maldivespost.com/\?lid=10\","
      "\"languages\":\"dv\""
      "}"));
  region_data.insert(std::make_pair("MW", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C %X\","
      "\"languages\":\"en~ny\""
      "}"));
  region_data.insert(std::make_pair("MX", "{"
      "\"fmt\":\"%N%n%O%n%A%n%D%n%Z %C, %S\","
      "\"require\":\"ACZ\","
      "\"state_name_type\":\"state\","
      "\"sublocality_name_type\":\"neighborhood\","
      "\"zipex\":\"02860,77520,06082\","
      "\"posturl\":\"http://www.correosdemexico.gob.mx/ServiciosLinea/Paginas/ccpostales.aspx\","
      "\"languages\":\"es\""
      "}"));
  region_data.insert(std::make_pair("MY", "{"
      "\"fmt\":\"%N%n%O%n%A%n%D%n%Z %C%n%S\","
      "\"require\":\"ACZ\","
      "\"state_name_type\":\"state\","
      "\"sublocality_name_type\":\"village_township\","
      "\"zipex\":\"43000,50754,88990,50670\","
      "\"posturl\":\"http://www.pos.com.my\","
      "\"languages\":\"ms\""
      "}"));
  region_data.insert(std::make_pair("MZ", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"1102,1119,3212\","
      "\"languages\":\"pt\""
      "}"));
  region_data.insert(std::make_pair("NA", "{"
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("NC", "{"
      "\"fmt\":\"%O%n%N%n%A%n%Z %C %X\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"98814,98800,98810\","
      "\"posturl\":\"http://poste.opt.nc/index.php\?option=com_content&view=article&id=80&Itemid=131\","
      "\"languages\":\"fr\""
      "}"));
  region_data.insert(std::make_pair("NE", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"8001\","
      "\"languages\":\"fr\""
      "}"));
  region_data.insert(std::make_pair("NF", "{"
      "\"fmt\":\"%O%n%N%n%A%n%C %S %Z\","
      "\"zipex\":\"2899\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("NG", "{"
      "\"fmt\":\"%N%n%O%n%A%n%D%n%C %Z%n%S\","
      "\"state_name_type\":\"state\","
      "\"zipex\":\"930283,300001,931104\","
      "\"posturl\":\"http://www.nigeriapostcodes.com/\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("NI", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z%n%C, %S\","
      "\"state_name_type\":\"department\","
      "\"zipex\":\"52000\","
      "\"posturl\":\"http://www.correos.gob.ni/index.php/codigo-postal-2\","
      "\"languages\":\"es\""
      "}"));
  region_data.insert(std::make_pair("NL", "{"
      "\"fmt\":\"%O%n%N%n%A%n%Z %C\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"1234 AB,2490 AA\","
      "\"posturl\":\"http://www.postnl.nl/voorthuis/\","
      "\"languages\":\"nl~fy\""
      "}"));
  region_data.insert(std::make_pair("NO", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"require\":\"ACZ\","
      "\"locality_name_type\":\"post_town\","
      "\"zipex\":\"0025,0107,6631\","
      "\"posturl\":\"http://adressesok.posten.no/nb/postal_codes/search\","
      "\"languages\":\"no~nn~se\""
      "}"));
  region_data.insert(std::make_pair("NP", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C %Z\","
      "\"zipex\":\"44601\","
      "\"posturl\":\"http://www.gpo.gov.np/postalcode.aspx\","
      "\"languages\":\"ne\""
      "}"));
  region_data.insert(std::make_pair("NR", "{"
      "\"fmt\":\"%N%n%O%n%A%n%S\","
      "\"require\":\"AS\","
      "\"state_name_type\":\"district\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("NU", "{"
      "\"languages\":\"en~niu\""
      "}"));
  region_data.insert(std::make_pair("NZ", "{"
      "\"fmt\":\"%N%n%O%n%A%n%D%n%C %Z\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"6001,6015,6332,8252,1030\","
      "\"posturl\":\"http://www.nzpost.co.nz/Cultures/en-NZ/OnlineTools/PostCodeFinder/\","
      "\"languages\":\"en~mi\""
      "}"));
  region_data.insert(std::make_pair("OM", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z%n%C\","
      "\"zipex\":\"133,112,111\","
      "\"languages\":\"ar\""
      "}"));
  region_data.insert(std::make_pair("PA", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C%n%S\","
      "\"languages\":\"es\""
      "}"));
  region_data.insert(std::make_pair("PE", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C %Z%n%S\","
      "\"zipex\":\"LIMA 23,LIMA 42,CALLAO 2,02001\","
      "\"posturl\":\"http://www.serpost.com.pe/cpostal/codigo\","
      "\"languages\":\"es~qu\""
      "}"));
  region_data.insert(std::make_pair("PF", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C %S\","
      "\"require\":\"ACSZ\","
      "\"state_name_type\":\"island\","
      "\"zipex\":\"98709\","
      "\"languages\":\"fr~ty\""
      "}"));
  region_data.insert(std::make_pair("PG", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C %Z %S\","
      "\"require\":\"ACS\","
      "\"zipex\":\"111\","
      "\"languages\":\"tpi~en~ho\""
      "}"));
  region_data.insert(std::make_pair("PH", "{"
      "\"fmt\":\"%N%n%O%n%A%n%D, %C%n%Z %S\","
      "\"zipex\":\"1008,1050,1135,1207,2000,1000\","
      "\"posturl\":\"http://www.philpost.gov.ph/\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("PK", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C-%Z\","
      "\"zipex\":\"44000\","
      "\"posturl\":\"http://www.pakpost.gov.pk/postcode/postcode.html\","
      "\"languages\":\"ur~en\""
      "}"));
  region_data.insert(std::make_pair("PL", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"00-950,05-470,48-300,32-015,00-940\","
      "\"posturl\":\"http://kody.poczta-polska.pl/\","
      "\"languages\":\"pl~de~csb~lt\""
      "}"));
  region_data.insert(std::make_pair("PM", "{"
      "\"fmt\":\"%O%n%N%n%A%n%Z %C %X\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"97500\","
      "\"languages\":\"fr\""
      "}"));
  region_data.insert(std::make_pair("PN", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C%n%Z\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"PCRN 1ZZ\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("PR", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C PR %Z\","
      "\"require\":\"ACZ\","
      "\"zip_name_type\":\"zip\","
      "\"zipex\":\"00930\","
      "\"posturl\":\"http://zip4.usps.com/zip4/welcome.jsp\","
      "\"languages\":\"es~en\""
      "}"));
  region_data.insert(std::make_pair("PS", "{"
      "\"languages\":\"ar\""
      "}"));
  region_data.insert(std::make_pair("PT", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"2725-079,1250-096,1201-950,2860-571,1208-148\","
      "\"posturl\":\"http://www.ctt.pt/feapl_2/app/open/tools.jspx\?tool=1\","
      "\"languages\":\"pt\""
      "}"));
  region_data.insert(std::make_pair("PW", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C %S %Z\","
      "\"require\":\"ACSZ\","
      "\"zip_name_type\":\"zip\","
      "\"state_name_type\":\"state\","
      "\"zipex\":\"96940\","
      "\"posturl\":\"http://zip4.usps.com/zip4/welcome.jsp\","
      "\"languages\":\"pau~en\""
      "}"));
  region_data.insert(std::make_pair("PY", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"1536,1538,1209\","
      "\"languages\":\"gn~es\""
      "}"));
  region_data.insert(std::make_pair("QA", "{"
      "\"languages\":\"ar\""
      "}"));
  region_data.insert(std::make_pair("RE", "{"
      "\"fmt\":\"%O%n%N%n%A%n%Z %C %X\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"97400\","
      "\"posturl\":\"http://www.laposte.fr/Particulier/Utiliser-nos-outils-pratiques/Outils-et-documents/Trouvez-un-code-postal\","
      "\"languages\":\"fr\""
      "}"));
  region_data.insert(std::make_pair("RO", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"060274,061357,200716\","
      "\"posturl\":\"http://www.posta-romana.ro/zip_codes\","
      "\"languages\":\"ro\""
      "}"));
  region_data.insert(std::make_pair("RS", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"106314\","
      "\"posturl\":\"http://www.posta.rs/struktura/lat/aplikacije/pronadji/nadji-postu.asp\","
      "\"languages\":\"sr~sr-Latn~hu~ro~hr~sk~uk\""
      "}"));
  region_data.insert(std::make_pair("RU", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C%n%S%n%Z\","
      "\"lfmt\":\"%N%n%O%n%A%n%C%n%S%n%Z\","
      "\"require\":\"ACSZ\","
      "\"state_name_type\":\"oblast\","
      "\"zipex\":\"247112,103375,188300\","
      "\"posturl\":\"http://info.russianpost.ru/servlet/department\","
      "\"languages\":\"ru\""
      "}"));
  region_data.insert(std::make_pair("RW", "{"
      "\"languages\":\"rw~en~fr\""
      "}"));
  region_data.insert(std::make_pair("SA", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C %Z\","
      "\"zipex\":\"11564,11187,11142\","
      "\"languages\":\"ar\""
      "}"));
  region_data.insert(std::make_pair("SB", "{"
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("SC", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C%n%S\","
      "\"state_name_type\":\"island\","
      "\"languages\":\"fr~en\""
      "}"));
  region_data.insert(std::make_pair("SE", "{"
      "\"fmt\":\"%O%n%N%n%A%nSE-%Z %C\","
      "\"require\":\"ACZ\","
      "\"locality_name_type\":\"post_town\","
      "\"zipex\":\"11455,12345,10500\","
      "\"posturl\":\"http://www.posten.se/sv/Kundservice/Sidor/Sok-postnummer-resultat.aspx\","
      "\"languages\":\"sv~fi\""
      "}"));
  region_data.insert(std::make_pair("SG", "{"
      "\"fmt\":\"%N%n%O%n%A%nSINGAPORE %Z\","
      "\"require\":\"AZ\","
      "\"zipex\":\"546080,308125,408600\","
      "\"posturl\":\"https://www.singpost.com/find-postal-code\","
      "\"languages\":\"en~zh~ms~ta\""
      "}"));
  region_data.insert(std::make_pair("SH", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C%n%Z\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"STHL 1ZZ\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("SI", "{"
      "\"fmt\":\"%N%n%O%n%A%nSI- %Z %C\","
      "\"zipex\":\"4000,1001,2500\","
      "\"languages\":\"sl\""
      "}"));
  region_data.insert(std::make_pair("SJ", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"require\":\"ACZ\","
      "\"locality_name_type\":\"post_town\","
      "\"zipex\":\"9170\","
      "\"posturl\":\"http://epab.posten.no/\","
      "\"languages\":\"no\""
      "}"));
  region_data.insert(std::make_pair("SK", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"010 01,023 14,972 48,921 01,975 99\","
      "\"posturl\":\"http://psc.posta.sk\","
      "\"languages\":\"sk\""
      "}"));
  region_data.insert(std::make_pair("SL", "{"
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("SM", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"require\":\"AZ\","
      "\"zipex\":\"47890,47891,47895,47899\","
      "\"posturl\":\"http://www.poste.it/online/cercacap/\","
      "\"languages\":\"it\""
      "}"));
  region_data.insert(std::make_pair("SN", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"12500,46024,16556,10000\","
      "\"languages\":\"wo~fr~ff~srr~dyo~sav~mfv~bjt~snf~knf~bsc~mey~tnr\""
      "}"));
  region_data.insert(std::make_pair("SO", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C, %S %Z\","
      "\"require\":\"ACS\","
      "\"zipex\":\"JH 09010,AD 11010\","
      "\"languages\":\"so\""
      "}"));
  region_data.insert(std::make_pair("SR", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C%n%S\","
      "\"languages\":\"nl\""
      "}"));
  region_data.insert(std::make_pair("SS", "{"
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("ST", "{"
      "\"languages\":\"pt\""
      "}"));
  region_data.insert(std::make_pair("SV", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z-%C%n%S\","
      "\"require\":\"ACS\","
      "\"zipex\":\"CP 1101\","
      "\"languages\":\"es\""
      "}"));
  region_data.insert(std::make_pair("SX", "{"
      "\"languages\":\"en~nl\""
      "}"));
  region_data.insert(std::make_pair("SZ", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C%n%Z\","
      "\"zipex\":\"H100\","
      "\"posturl\":\"http://www.sptc.co.sz/swazipost/codes/index.php\","
      "\"languages\":\"en~ss\""
      "}"));
  region_data.insert(std::make_pair("TA", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C%n%Z\","
      "\"zipex\":\"TDCU 1ZZ\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("TC", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C%n%Z\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"TKCA 1ZZ\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("TD", "{"
      "\"languages\":\"fr~ar\""
      "}"));
  region_data.insert(std::make_pair("TF", "{"
      "\"languages\":\"fr\""
      "}"));
  region_data.insert(std::make_pair("TG", "{"
      "\"languages\":\"fr\""
      "}"));
  region_data.insert(std::make_pair("TH", "{"
      "\"fmt\":\"%N%n%O%n%A%n%D %C%n%S %Z\","
      "\"lfmt\":\"%N%n%O%n%A%n%D, %C%n%S %Z\","
      "\"zipex\":\"10150,10210\","
      "\"languages\":\"th\""
      "}"));
  region_data.insert(std::make_pair("TJ", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"735450,734025\","
      "\"languages\":\"tg\""
      "}"));
  region_data.insert(std::make_pair("TK", "{"
      "\"languages\":\"en~tkl\""
      "}"));
  region_data.insert(std::make_pair("TL", "{"
      "\"languages\":\"pt~tet\""
      "}"));
  region_data.insert(std::make_pair("TM", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"744000\","
      "\"languages\":\"tk\""
      "}"));
  region_data.insert(std::make_pair("TN", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"1002,8129,3100,1030\","
      "\"posturl\":\"http://www.poste.tn/codes.php\","
      "\"languages\":\"ar~fr\""
      "}"));
  region_data.insert(std::make_pair("TO", "{"
      "\"languages\":\"to~en\""
      "}"));
  region_data.insert(std::make_pair("TR", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C/%S\","
      "\"require\":\"ACZ\","
      "\"locality_name_type\":\"district\","
      "\"zipex\":\"01960,06101\","
      "\"posturl\":\"http://postakodu.ptt.gov.tr/\","
      "\"languages\":\"tr\""
      "}"));
  region_data.insert(std::make_pair("TT", "{"
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("TV", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C%n%S\","
      "\"state_name_type\":\"island\","
      "\"languages\":\"tyv\""
      "}"));
  region_data.insert(std::make_pair("TW", "{"
      "\"fmt\":\"%Z%n%S%C%n%A%n%O%n%N\","
      "\"lfmt\":\"%N%n%O%n%A%n%C, %S %Z\","
      "\"require\":\"ACSZ\","
      "\"state_name_type\":\"county\","
      "\"zipex\":\"104,106,10603,40867\","
      "\"posturl\":\"http://www.post.gov.tw/post/internet/f_searchzone/index.jsp\?ID=190102\","
      "\"languages\":\"zh-Hant\""
      "}"));
  region_data.insert(std::make_pair("TZ", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"6090,34413\","
      "\"languages\":\"sw~en\""
      "}"));
  region_data.insert(std::make_pair("UA", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C%n%S%n%Z\","
      "\"lfmt\":\"%N%n%O%n%A%n%C%n%S%n%Z\","
      "\"require\":\"ACSZ\","
      "\"state_name_type\":\"oblast\","
      "\"zipex\":\"15432,01055,01001\","
      "\"posturl\":\"http://services.ukrposhta.com/postindex_new/\","
      "\"languages\":\"uk\""
      "}"));
  region_data.insert(std::make_pair("UG", "{"
      "\"languages\":\"sw~en\""
      "}"));
  region_data.insert(std::make_pair("UM", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C %S %Z\","
      "\"require\":\"ACS\","
      "\"zip_name_type\":\"zip\","
      "\"state_name_type\":\"state\","
      "\"zipex\":\"96898\","
      "\"posturl\":\"http://zip4.usps.com/zip4/welcome.jsp\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("US", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C, %S %Z\","
      "\"require\":\"ACSZ\","
      "\"zip_name_type\":\"zip\","
      "\"state_name_type\":\"state\","
      "\"zipex\":\"95014,22162-1010\","
      "\"posturl\":\"https://tools.usps.com/go/ZipLookupAction!input.action\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("UY", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C %S\","
      "\"zipex\":\"11600\","
      "\"posturl\":\"http://www.correo.com.uy/index.asp\?codPag=codPost&switchMapa=codPost\","
      "\"languages\":\"es\""
      "}"));
  region_data.insert(std::make_pair("UZ", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C%n%S\","
      "\"zipex\":\"702100,700000\","
      "\"posturl\":\"http://www.pochta.uz/ru/uslugi/indexsearch.html\","
      "\"languages\":\"uz~uz-Cyrl\""
      "}"));
  region_data.insert(std::make_pair("VA", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"00120\","
      "\"languages\":\"it\""
      "}"));
  region_data.insert(std::make_pair("VC", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C %Z\","
      "\"zipex\":\"VC0100,VC0110,VC0400\","
      "\"posturl\":\"http://www.svgpost.gov.vc/\?option=com_content&view=article&id=3&Itemid=16\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("VE", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C %Z, %S\","
      "\"require\":\"ACS\","
      "\"state_name_type\":\"state\","
      "\"zipex\":\"1010,3001,8011,1020\","
      "\"posturl\":\"http://www.ipostel.gob.ve/index.php/oficinas-postales\","
      "\"languages\":\"es\""
      "}"));
  region_data.insert(std::make_pair("VG", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C%n%Z\","
      "\"require\":\"A\","
      "\"zipex\":\"VG1110,VG1150,VG1160\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("VI", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C %S %Z\","
      "\"require\":\"ACSZ\","
      "\"zip_name_type\":\"zip\","
      "\"state_name_type\":\"state\","
      "\"zipex\":\"00802-1222,00850-9802\","
      "\"posturl\":\"http://zip4.usps.com/zip4/welcome.jsp\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("VN", "{"
      "\"fmt\":\"%N%n%O%n%A%n%C%n%S %Z\","
      "\"lfmt\":\"%N%n%O%n%A%n%C%n%S %Z\","
      "\"zipex\":\"119415,136065,720344\","
      "\"posturl\":\"http://postcode.vnpost.vn/services/search.aspx\","
      "\"languages\":\"vi\""
      "}"));
  region_data.insert(std::make_pair("VU", "{"
      "\"languages\":\"bi~en~fr\""
      "}"));
  region_data.insert(std::make_pair("WF", "{"
      "\"fmt\":\"%O%n%N%n%A%n%Z %C %X\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"98600\","
      "\"languages\":\"fr\""
      "}"));
  region_data.insert(std::make_pair("WS", "{"
      "\"languages\":\"sm~en\""
      "}"));
  region_data.insert(std::make_pair("XK", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"10000\","
      "\"languages\":\"sq~sr~sr-Latn\""
      "}"));
  region_data.insert(std::make_pair("YE", "{"
      "\"languages\":\"ar\""
      "}"));
  region_data.insert(std::make_pair("YT", "{"
      "\"fmt\":\"%O%n%N%n%A%n%Z %C %X\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"97600\","
      "\"languages\":\"fr\""
      "}"));
  region_data.insert(std::make_pair("ZA", "{"
      "\"fmt\":\"%N%n%O%n%A%n%D%n%C%n%Z\","
      "\"require\":\"ACZ\","
      "\"zipex\":\"0083,1451,0001\","
      "\"posturl\":\"https://www.postoffice.co.za/contactus/postalcode.html\","
      "\"languages\":\"en~zu~xh~af~nso~tn~st~ts~ss~ve~nr\""
      "}"));
  region_data.insert(std::make_pair("ZM", "{"
      "\"fmt\":\"%N%n%O%n%A%n%Z %C\","
      "\"zipex\":\"50100,50101\","
      "\"languages\":\"en\""
      "}"));
  region_data.insert(std::make_pair("ZW", "{"
      "\"languages\":\"sn~en~nd\""
      "}"));
  return region_data;
}

}  // namespace

// static
const std::string& RegionDataConstants::GetDefaultRegionData() {
  static const std::string kDefaultRegionData(
      "{"
      "\"fmt\":\"%N%n%O%n%A%n%C\","
      "\"require\":\"AC\","
      "\"zip_name_type\":\"postal\","
      "\"state_name_type\":\"province\","
      "\"locality_name_type\":\"city\","
      "\"sublocality_name_type\":\"suburb\""
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
  for (std::map<std::string, std::string>::const_iterator
       it = GetAllRegionData().begin(); it != GetAllRegionData().end(); ++it) {
    std::vector<FormatElement> fields;
    // Here it->second actually contains the entire JSON blob for this region,
    // and not only the format field, but it doesn't really matter when just
    // checking whether a particular formatting code (eg. "%C") is present, as
    // there isn't anything else in the JSON that erroneously could match a
    // formatting code.
    ParseFormatRule(it->second, &fields);
    size_t depth = 1;
    for (; depth < arraysize(LookupKey::kHierarchy); ++depth) {
      AddressField field = LookupKey::kHierarchy[depth];
      // Check to see if a particular field in the hierarchy is used by
      // addresses in this country. If not, the maximum depth has been reached.
      if (std::find(fields.begin(), fields.end(), FormatElement(field)) ==
          fields.end()) {
        break;
      }
    }
    max_depth.insert(std::make_pair(it->first, depth - 1));
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
  std::map<std::string, std::string>::const_iterator it =
      GetAllRegionData().find(region_code);
  return it != GetAllRegionData().end() ? it->second : kEmptyString;
}

// static
size_t RegionDataConstants::GetMaxLookupKeyDepth(
    const std::string& region_code) {
  static const std::map<std::string, size_t> kMaxDepth(InitMaxLookupKeyDepth());
  std::map<std::string, size_t>::const_iterator it =
      kMaxDepth.find(region_code);
  return it != kMaxDepth.end() ? it->second : 0;
}

}  // namespace addressinput
}  // namespace i18n
