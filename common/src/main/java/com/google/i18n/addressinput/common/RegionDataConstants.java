// Copyright (C) 2010 Google Inc.
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
//
package com.google.i18n.addressinput.common;

import java.util.Collections;
import java.util.Map;
import java.util.TreeMap;

/**
 * Initial data in JSON format for regions. This has some formatting information for some countries,
 * and a list of all the regions that the widget can support.
 *
 * <p>AUTOMATICALLY GENERATED FILE - DO NOT EDIT<br>
 */
public final class RegionDataConstants {
  private static final Map<String, String> addressDataMap = createMap();

  public static Map<String, String> getCountryFormatMap() {
    return addressDataMap;
  }

  private static Map<String, String> createMap() {
    TreeMap<String, String> map = new TreeMap<String, String>();
    map.put("AC", "{\"name\":\"ASCENSION ISLAND\",\"fmt\":\"%N%n%O%n%A%n%C%n%Z\"}");
    map.put("AD", "{\"name\":\"ANDORRA\",\"lang\":\"ca\",\"languages\":\"ca\",\"fmt\":\"%N%n%O%n%A%n%Z %C\"}");
    map.put("AE", "{\"name\":\"UNITED ARAB EMIRATES\",\"lang\":\"ar\",\"languages\":\"ar\",\"lfmt\":\"%N%n%O%n%A%n%S\",\"fmt\":\"%N%n%O%n%A%n%S\",\"require\":\"AS\",\"state_name_type\":\"emirate\"}");
    map.put("AF", "{\"name\":\"AFGHANISTAN\",\"fmt\":\"%N%n%O%n%A%n%C%n%Z\"}");
    map.put("AG", "{\"name\":\"ANTIGUA AND BARBUDA\",\"require\":\"A\"}");
    map.put("AI", "{\"name\":\"ANGUILLA\",\"fmt\":\"%N%n%O%n%A%n%C%n%Z\"}");
    map.put("AL", "{\"name\":\"ALBANIA\",\"fmt\":\"%N%n%O%n%A%n%Z%n%C\"}");
    map.put("AM", "{\"name\":\"ARMENIA\",\"lang\":\"hy\",\"languages\":\"hy\",\"lfmt\":\"%N%n%O%n%A%n%Z%n%C%n%S\",\"fmt\":\"%N%n%O%n%A%n%Z%n%C%n%S\"}");
    map.put("AO", "{\"name\":\"ANGOLA\"}");
    map.put("AQ", "{\"name\":\"ANTARCTICA\"}");
    map.put("AR", "{\"name\":\"ARGENTINA\",\"lang\":\"es\",\"languages\":\"es\",\"fmt\":\"%N%n%O%n%A%n%Z %C%n%S\",\"upper\":\"ACZ\"}");
    map.put("AS", "{\"name\":\"AMERICAN SAMOA\",\"fmt\":\"%N%n%O%n%A%n%C %S %Z\",\"require\":\"ACSZ\",\"upper\":\"ACNOS\",\"state_name_type\":\"state\",\"zip_name_type\":\"zip\"}");
    map.put("AT", "{\"name\":\"AUSTRIA\",\"fmt\":\"%O%n%N%n%A%n%Z %C\",\"require\":\"ACZ\"}");
    map.put("AU", "{\"name\":\"AUSTRALIA\",\"lang\":\"en\",\"languages\":\"en\",\"fmt\":\"%O%n%N%n%A%n%C %S %Z\",\"require\":\"ACSZ\",\"upper\":\"CS\",\"locality_name_type\":\"suburb\",\"state_name_type\":\"state\"}");
    map.put("AW", "{\"name\":\"ARUBA\"}");
    map.put("AX", "{\"name\":\"FINLAND\",\"fmt\":\"%O%n%N%n%A%nAX-%Z %C%nÅLAND\",\"require\":\"ACZ\",\"postprefix\":\"AX-\"}");
    map.put("AZ", "{\"name\":\"AZERBAIJAN\",\"fmt\":\"%N%n%O%n%A%nAZ %Z %C\",\"postprefix\":\"AZ \"}");
    map.put("BA", "{\"name\":\"BOSNIA AND HERZEGOVINA\",\"fmt\":\"%N%n%O%n%A%n%Z %C\"}");
    map.put("BB", "{\"name\":\"BARBADOS\",\"fmt\":\"%N%n%O%n%A%n%C, %S %Z\",\"state_name_type\":\"parish\"}");
    map.put("BD", "{\"name\":\"BANGLADESH\",\"fmt\":\"%N%n%O%n%A%n%C - %Z\"}");
    map.put("BE", "{\"name\":\"BELGIUM\",\"fmt\":\"%O%n%N%n%A%n%Z %C\",\"require\":\"ACZ\"}");
    map.put("BF", "{\"name\":\"BURKINA FASO\",\"fmt\":\"%N%n%O%n%A%n%C %X\"}");
    map.put("BG", "{\"name\":\"BULGARIA (REP.)\",\"fmt\":\"%N%n%O%n%A%n%Z %C\"}");
    map.put("BH", "{\"name\":\"BAHRAIN\",\"fmt\":\"%N%n%O%n%A%n%C %Z\"}");
    map.put("BI", "{\"name\":\"BURUNDI\"}");
    map.put("BJ", "{\"name\":\"BENIN\",\"upper\":\"AC\"}");
    map.put("BL", "{\"name\":\"SAINT BARTHELEMY\",\"fmt\":\"%O%n%N%n%A%n%Z %C %X\",\"require\":\"ACZ\",\"upper\":\"ACX\"}");
    map.put("BM", "{\"name\":\"BERMUDA\",\"fmt\":\"%N%n%O%n%A%n%C %Z\"}");
    map.put("BN", "{\"name\":\"BRUNEI DARUSSALAM\",\"fmt\":\"%N%n%O%n%A%n%C %Z\"}");
    map.put("BO", "{\"name\":\"BOLIVIA\",\"upper\":\"AC\"}");
    map.put("BQ", "{\"name\":\"BONAIRE, SINT EUSTATIUS, AND SABA\"}");
    map.put("BR", "{\"name\":\"BRAZIL\",\"lang\":\"pt\",\"languages\":\"pt\",\"fmt\":\"%O%n%N%n%A%n%D%n%C-%S%n%Z\",\"require\":\"ASCZ\",\"upper\":\"CS\",\"sublocality_name_type\":\"neighborhood\",\"state_name_type\":\"state\",\"width_overrides\":\"%C:L%S:S\",\"label_overrides\":[{\"field\":\"S2\",\"label\":\"Setor/ADE/Folha\"},{\"field\":\"S3\",\"label\":\"Quadra\"},{\"field\":\"S4\",\"label\":\"Trecho/AE/Modulo\"},{\"field\":\"S5\",\"label\":\"Cj/Bl/MI/Projeção/Etapa\"},{\"field\":\"LP\",\"label\":\"Lote\"},{\"field\":\"BI\",\"label\":\"Casa/Comercio\"},{\"field\":\"CG\",\"label\":\"Complexo/Chácara\"}]}");
    map.put("BS", "{\"name\":\"BAHAMAS\",\"lang\":\"en\",\"languages\":\"en\",\"fmt\":\"%N%n%O%n%A%n%C, %S\",\"state_name_type\":\"island\"}");
    map.put("BT", "{\"name\":\"BHUTAN\",\"fmt\":\"%N%n%O%n%A%n%C %Z\"}");
    map.put("BV", "{\"name\":\"BOUVET ISLAND\"}");
    map.put("BW", "{\"name\":\"BOTSWANA\"}");
    map.put("BY", "{\"name\":\"BELARUS\",\"fmt\":\"%S%n%Z %C%n%A%n%O%n%N\"}");
    map.put("BZ", "{\"name\":\"BELIZE\"}");
    map.put("CA", "{\"name\":\"CANADA\",\"lang\":\"en\",\"languages\":\"en~fr\",\"fmt\":\"%N%n%O%n%A%n%C %S %Z\",\"require\":\"ACSZ\",\"upper\":\"ACNOSZ\"}");
    map.put("CC", "{\"name\":\"COCOS (KEELING) ISLANDS\",\"fmt\":\"%O%n%N%n%A%n%C %S %Z\",\"upper\":\"CS\"}");
    map.put("CD", "{\"name\":\"CONGO (DEM. REP.)\"}");
    map.put("CF", "{\"name\":\"CENTRAL AFRICAN REPUBLIC\"}");
    map.put("CG", "{\"name\":\"CONGO (REP.)\"}");
    map.put("CH", "{\"name\":\"SWITZERLAND\",\"fmt\":\"%O%n%N%n%A%nCH-%Z %C\",\"require\":\"ACZ\",\"upper\":\"\",\"postprefix\":\"CH-\"}");
    map.put("CI", "{\"name\":\"COTE D'IVOIRE\",\"fmt\":\"%N%n%O%n%X %A %C %X\"}");
    map.put("CK", "{\"name\":\"COOK ISLANDS\"}");
    map.put("CL", "{\"name\":\"CHILE\",\"lang\":\"es\",\"languages\":\"es\",\"fmt\":\"%N%n%O%n%A%n%Z %C%n%S\"}");
    map.put("CM", "{\"name\":\"CAMEROON\"}");
    map.put("CN", "{\"name\":\"CHINA\",\"lang\":\"zh\",\"languages\":\"zh\",\"lfmt\":\"%N%n%O%n%A%n%D%n%C%n%S, %Z\",\"fmt\":\"%Z%n%S%C%D%n%A%n%O%n%N\",\"require\":\"ACSZ\",\"upper\":\"S\",\"sublocality_name_type\":\"district\",\"width_overrides\":\"%S:S%C:S%D:S\",\"label_overrides\":[{\"field\":\"C\",\"label\":\"市/自治州/地区/盟\",\"lang\":\"zh\"},{\"field\":\"S\",\"label\":\"省/自治区/直辖市\",\"lang\":\"zh\"},{\"field\":\"D\",\"label\":\"区/县/旗\",\"lang\":\"zh\"}]}");
    map.put("CO", "{\"name\":\"COLOMBIA\",\"fmt\":\"%N%n%O%n%A%n%C, %S, %Z\",\"require\":\"AS\",\"state_name_type\":\"department\",\"label_overrides\":[{\"field\":\"LL\",\"label\":\"Vereda\"},{\"field\":\"A3\",\"label\":\"Corregimiento\"},{\"field\":\"A2\",\"label\":\"Municipio\"}]}");
    map.put("CR", "{\"name\":\"COSTA RICA\",\"fmt\":\"%N%n%O%n%A%n%S, %C%n%Z\",\"require\":\"ACS\"}");
    map.put("CU", "{\"name\":\"CUBA\",\"lang\":\"es\",\"languages\":\"es\",\"fmt\":\"%N%n%O%n%A%n%C %S%n%Z\"}");
    map.put("CV", "{\"name\":\"CAPE VERDE\",\"lang\":\"pt\",\"languages\":\"pt\",\"fmt\":\"%N%n%O%n%A%n%Z %C%n%S\",\"state_name_type\":\"island\"}");
    map.put("CW", "{\"name\":\"CURACAO\"}");
    map.put("CX", "{\"name\":\"CHRISTMAS ISLAND\",\"fmt\":\"%O%n%N%n%A%n%C %S %Z\",\"upper\":\"CS\"}");
    map.put("CY", "{\"name\":\"CYPRUS\",\"fmt\":\"%N%n%O%n%A%n%Z %C\"}");
    map.put("CZ", "{\"name\":\"CZECH REP.\",\"fmt\":\"%N%n%O%n%A%n%Z %C\",\"require\":\"ACZ\",\"label_overrides\":[{\"field\":\"NH\",\"label\":\"Obecní část\",\"lang\":\"cs\"},{\"field\":\"NH\",\"label\":\"Obecný časť\",\"lang\":\"sk\"},{\"field\":\"BI\",\"label\":\"Descriptive No.\"},{\"field\":\"BI\",\"label\":\"Popisné číslo\",\"lang\":\"cs\"},{\"field\":\"BI\",\"label\":\"Súpisné číslo\",\"lang\":\"sk\"},{\"field\":\"SN\",\"label\":\"Orientation No.\"},{\"field\":\"SN\",\"label\":\"Orientační číslo\",\"lang\":\"cs\"},{\"field\":\"SN\",\"label\":\"Orientačné číslo\",\"lang\":\"sk\"},{\"field\":\"S1\",\"label\":\"City District\"},{\"field\":\"S1\",\"label\":\"Městská část\",\"lang\":\"cs\"},{\"field\":\"S1\",\"label\":\"Mestská časť\",\"lang\":\"sk\"}]}");
    map.put("DE", "{\"name\":\"GERMANY\",\"fmt\":\"%N%n%O%n%A%n%Z %C\",\"require\":\"ACZ\"}");
    map.put("DJ", "{\"name\":\"DJIBOUTI\"}");
    map.put("DK", "{\"name\":\"DENMARK\",\"fmt\":\"%N%n%O%n%A%n%Z %C\",\"require\":\"ACZ\"}");
    map.put("DM", "{\"name\":\"DOMINICA\"}");
    map.put("DO", "{\"name\":\"DOMINICAN REP.\",\"fmt\":\"%N%n%O%n%A%n%Z %C\"}");
    map.put("DZ", "{\"name\":\"ALGERIA\",\"fmt\":\"%N%n%O%n%A%n%Z %C\"}");
    map.put("EC", "{\"name\":\"ECUADOR\",\"fmt\":\"%N%n%O%n%A%n%Z%n%C\",\"upper\":\"CZ\"}");
    map.put("EE", "{\"name\":\"ESTONIA\",\"fmt\":\"%N%n%O%n%A%n%Z %C\",\"require\":\"ACZ\",\"label_overrides\":[{\"field\":\"C\",\"label\":\"Linn/vald\",\"lang\":\"et\"},{\"field\":\"C\",\"label\":\"City/Parish\",\"lang\":\"en\"}]}");
    map.put("EG", "{\"name\":\"EGYPT\",\"lang\":\"ar\",\"languages\":\"ar\",\"lfmt\":\"%N%n%O%n%A%n%C%n%S%n%Z\",\"fmt\":\"%N%n%O%n%A%n%C%n%S%n%Z\"}");
    map.put("EH", "{\"name\":\"WESTERN SAHARA\",\"fmt\":\"%N%n%O%n%A%n%Z %C\"}");
    map.put("ER", "{\"name\":\"ERITREA\"}");
    map.put("ES", "{\"name\":\"SPAIN\",\"lang\":\"es\",\"languages\":\"es~ca~gl~eu\",\"fmt\":\"%N%n%O%n%A%n%Z %C %S\",\"require\":\"ACSZ\",\"upper\":\"CS\",\"width_overrides\":\"%S:S\"}");
    map.put("ET", "{\"name\":\"ETHIOPIA\",\"fmt\":\"%N%n%O%n%A%n%Z %C\"}");
    map.put("FI", "{\"name\":\"FINLAND\",\"fmt\":\"%O%n%N%n%A%nFI-%Z %C\",\"require\":\"ACZ\",\"postprefix\":\"FI-\"}");
    map.put("FJ", "{\"name\":\"FIJI\"}");
    map.put("FK", "{\"name\":\"FALKLAND ISLANDS (MALVINAS)\",\"fmt\":\"%N%n%O%n%A%n%C%n%Z\",\"require\":\"ACZ\",\"upper\":\"CZ\"}");
    map.put("FM", "{\"name\":\"MICRONESIA (Federated State of)\",\"fmt\":\"%N%n%O%n%A%n%C %S %Z\",\"require\":\"ACSZ\",\"upper\":\"ACNOS\",\"state_name_type\":\"state\",\"zip_name_type\":\"zip\"}");
    map.put("FO", "{\"name\":\"FAROE ISLANDS\",\"fmt\":\"%N%n%O%n%A%nFO%Z %C\",\"postprefix\":\"FO\"}");
    map.put("FR", "{\"name\":\"FRANCE\",\"fmt\":\"%O%n%N%n%A%n%Z %C\",\"require\":\"ACZ\",\"upper\":\"CX\"}");
    map.put("GA", "{\"name\":\"GABON\"}");
    map.put("GB", "{\"name\":\"UNITED KINGDOM\",\"fmt\":\"%N%n%O%n%A%n%C%n%Z\",\"require\":\"ACZ\",\"upper\":\"CZ\",\"locality_name_type\":\"post_town\",\"label_overrides\":[{\"field\":\"LL\",\"message\":\"MSG_DEPENDENT_LOCALITY_LABEL\"},{\"field\":\"Z\",\"label\":\"Postcode\",\"lang\":\"en\"}]}");
    map.put("GD", "{\"name\":\"GRENADA (WEST INDIES)\"}");
    map.put("GE", "{\"name\":\"GEORGIA\",\"fmt\":\"%N%n%O%n%A%n%Z %C\"}");
    map.put("GF", "{\"name\":\"FRENCH GUIANA\",\"fmt\":\"%O%n%N%n%A%n%Z %C %X\",\"require\":\"ACZ\",\"upper\":\"ACX\"}");
    map.put("GG", "{\"name\":\"CHANNEL ISLANDS\",\"fmt\":\"%N%n%O%n%A%n%C%nGUERNSEY%n%Z\",\"require\":\"ACZ\",\"upper\":\"CZ\"}");
    map.put("GH", "{\"name\":\"GHANA\"}");
    map.put("GI", "{\"name\":\"GIBRALTAR\",\"fmt\":\"%N%n%O%n%A%nGIBRALTAR%n%Z\",\"require\":\"A\"}");
    map.put("GL", "{\"name\":\"GREENLAND\",\"fmt\":\"%N%n%O%n%A%n%Z %C\",\"require\":\"ACZ\"}");
    map.put("GM", "{\"name\":\"GAMBIA\"}");
    map.put("GN", "{\"name\":\"GUINEA\",\"fmt\":\"%N%n%O%n%Z %A %C\"}");
    map.put("GP", "{\"name\":\"GUADELOUPE\",\"fmt\":\"%O%n%N%n%A%n%Z %C %X\",\"require\":\"ACZ\",\"upper\":\"ACX\"}");
    map.put("GQ", "{\"name\":\"EQUATORIAL GUINEA\"}");
    map.put("GR", "{\"name\":\"GREECE\",\"fmt\":\"%N%n%O%n%A%n%Z %C\",\"require\":\"ACZ\"}");
    map.put("GS", "{\"name\":\"SOUTH GEORGIA\",\"fmt\":\"%N%n%O%n%A%n%n%C%n%Z\",\"require\":\"ACZ\",\"upper\":\"CZ\"}");
    map.put("GT", "{\"name\":\"GUATEMALA\",\"fmt\":\"%N%n%O%n%A%n%Z- %C\"}");
    map.put("GU", "{\"name\":\"GUAM\",\"fmt\":\"%N%n%O%n%A%n%C %Z\",\"require\":\"ACZ\",\"upper\":\"ACNO\",\"zip_name_type\":\"zip\"}");
    map.put("GW", "{\"name\":\"GUINEA-BISSAU\",\"fmt\":\"%N%n%O%n%A%n%Z %C\"}");
    map.put("GY", "{\"name\":\"GUYANA\"}");
    map.put("HK", "{\"name\":\"HONG KONG\",\"lang\":\"zh-Hant\",\"languages\":\"zh-Hant~en\",\"lfmt\":\"%N%n%O%n%A%n%C%n%S\",\"fmt\":\"%S%n%C%n%A%n%O%n%N\",\"require\":\"AS\",\"upper\":\"S\",\"locality_name_type\":\"district\",\"state_name_type\":\"area\",\"width_overrides\":\"%S:S%C:L\",\"label_overrides\":[{\"field\":\"C\",\"label\":\"地区\",\"lang\":\"zh\"},{\"field\":\"C\",\"label\":\"地區\",\"lang\":\"zh-HK\"},{\"field\":\"C\",\"label\":\"地區\",\"lang\":\"zh-TW\"},{\"field\":\"CS\",\"label\":\"Flat / Room\",\"lang\":\"en\"},{\"field\":\"CS\",\"label\":\"單位編號\",\"lang\":\"zh-HK\"},{\"field\":\"BG\",\"label\":\"大廈名稱\",\"lang\":\"zh-HK\"}]}");
    map.put("HM", "{\"name\":\"HEARD AND MCDONALD ISLANDS\",\"fmt\":\"%O%n%N%n%A%n%C %S %Z\",\"upper\":\"CS\"}");
    map.put("HN", "{\"name\":\"HONDURAS\",\"fmt\":\"%N%n%O%n%A%n%C, %S%n%Z\",\"require\":\"ACS\"}");
    map.put("HR", "{\"name\":\"CROATIA\",\"fmt\":\"%N%n%O%n%A%nHR-%Z %C\",\"postprefix\":\"HR-\"}");
    map.put("HT", "{\"name\":\"HAITI\",\"fmt\":\"%N%n%O%n%A%nHT%Z %C\",\"postprefix\":\"HT\"}");
    map.put("HU", "{\"name\":\"HUNGARY (Rep.)\",\"fmt\":\"%N%n%O%n%C%n%A%n%Z\",\"require\":\"ACZ\",\"upper\":\"ACNO\"}");
    map.put("ID", "{\"name\":\"INDONESIA\",\"lang\":\"id\",\"languages\":\"id\",\"fmt\":\"%N%n%O%n%A%n%C%n%S %Z\",\"require\":\"AS\",\"label_overrides\":[{\"field\":\"A7\",\"label\":\"RT\"},{\"field\":\"A6\",\"label\":\"RW\"},{\"field\":\"A5\",\"label\":\"Dusun/Banjar\"},{\"field\":\"BI\",\"label\":\"Blok\"},{\"field\":\"A4\",\"message\":\"MSG_VILLAGE\"},{\"field\":\"A3\",\"label\":\"Kecamatan\"},{\"field\":\"S1\",\"label\":\"Pasar\"}]}");
    map.put("IE", "{\"name\":\"IRELAND\",\"lang\":\"en\",\"languages\":\"en\",\"fmt\":\"%N%n%O%n%A%n%D%n%C%n%S %Z\",\"sublocality_name_type\":\"townland\",\"state_name_type\":\"county\",\"zip_name_type\":\"eircode\",\"label_overrides\":[{\"field\":\"S\",\"label\":\"郡\",\"lang\":\"zh\"}]}");
    map.put("IL", "{\"name\":\"ISRAEL\",\"fmt\":\"%N%n%O%n%A%n%C %Z\"}");
    map.put("IM", "{\"name\":\"ISLE OF MAN\",\"fmt\":\"%N%n%O%n%A%n%C%n%Z\",\"require\":\"ACZ\",\"upper\":\"CZ\"}");
    map.put("IN", "{\"name\":\"INDIA\",\"lang\":\"en\",\"languages\":\"en~hi\",\"fmt\":\"%N%n%O%n%A%n%C %Z%n%S\",\"require\":\"ACSZ\",\"state_name_type\":\"state\",\"zip_name_type\":\"pin\",\"label_overrides\":[{\"field\":\"S1\",\"label\":\"Sublocality 1\"},{\"field\":\"S2\",\"label\":\"Sublocality 2\"},{\"field\":\"S3\",\"label\":\"Sublocality 3\"},{\"field\":\"S4\",\"label\":\"Sublocality 4\"}]}");
    map.put("IO", "{\"name\":\"BRITISH INDIAN OCEAN TERRITORY\",\"fmt\":\"%N%n%O%n%A%n%C%n%Z\",\"require\":\"ACZ\",\"upper\":\"CZ\"}");
    map.put("IQ", "{\"name\":\"IRAQ\",\"fmt\":\"%O%n%N%n%A%n%C, %S%n%Z\",\"require\":\"ACS\",\"upper\":\"CS\"}");
    map.put("IR", "{\"name\":\"IRAN\",\"lang\":\"fa\",\"languages\":\"fa\",\"fmt\":\"%O%n%N%n%S%n%C, %D%n%A%n%Z\",\"sublocality_name_type\":\"neighborhood\"}");
    map.put("IS", "{\"name\":\"ICELAND\",\"fmt\":\"%N%n%O%n%A%n%Z %C\"}");
    map.put("IT", "{\"name\":\"ITALY\",\"lang\":\"it\",\"languages\":\"it\",\"fmt\":\"%N%n%O%n%A%n%Z %C %S\",\"require\":\"ACSZ\",\"upper\":\"CS\",\"width_overrides\":\"%S:S\"}");
    map.put("JE", "{\"name\":\"CHANNEL ISLANDS\",\"fmt\":\"%N%n%O%n%A%n%C%nJERSEY%n%Z\",\"require\":\"ACZ\",\"upper\":\"CZ\"}");
    map.put("JM", "{\"name\":\"JAMAICA\",\"lang\":\"en\",\"languages\":\"en\",\"fmt\":\"%N%n%O%n%A%n%C%n%S %X\",\"require\":\"ACS\",\"state_name_type\":\"parish\"}");
    map.put("JO", "{\"name\":\"JORDAN\",\"fmt\":\"%N%n%O%n%A%n%C %Z\"}");
    map.put("JP", "{\"name\":\"JAPAN\",\"lang\":\"ja\",\"languages\":\"ja\",\"lfmt\":\"%N%n%O%n%A, %S%n%Z\",\"fmt\":\"〒%Z%n%S%n%A%n%O%n%N\",\"require\":\"ASZ\",\"upper\":\"S\",\"state_name_type\":\"prefecture\",\"width_overrides\":\"%S:S\"}");
    map.put("KE", "{\"name\":\"KENYA\",\"fmt\":\"%N%n%O%n%A%n%C%n%Z\"}");
    map.put("KG", "{\"name\":\"KYRGYZSTAN\",\"fmt\":\"%N%n%O%n%A%n%Z %C\"}");
    map.put("KH", "{\"name\":\"CAMBODIA\",\"fmt\":\"%N%n%O%n%A%n%C %Z\"}");
    map.put("KI", "{\"name\":\"KIRIBATI\",\"fmt\":\"%N%n%O%n%A%n%S%n%C\",\"upper\":\"ACNOS\",\"state_name_type\":\"island\"}");
    map.put("KM", "{\"name\":\"COMOROS\",\"upper\":\"AC\"}");
    map.put("KN", "{\"name\":\"SAINT KITTS AND NEVIS\",\"lang\":\"en\",\"languages\":\"en\",\"fmt\":\"%N%n%O%n%A%n%C, %S\",\"require\":\"ACS\",\"state_name_type\":\"island\"}");
    map.put("KP", "{\"name\":\"NORTH KOREA\",\"lang\":\"ko\",\"languages\":\"ko\",\"lfmt\":\"%N%n%O%n%A%n%C%n%S, %Z\",\"fmt\":\"%Z%n%S%n%C%n%A%n%O%n%N\"}");
    map.put("KR", "{\"name\":\"SOUTH KOREA\",\"lang\":\"ko\",\"languages\":\"ko\",\"lfmt\":\"%N%n%O%n%A%n%D%n%C%n%S%n%Z\",\"fmt\":\"%S %C%D%n%A%n%O%n%N%n%Z\",\"require\":\"ACSZ\",\"upper\":\"Z\",\"sublocality_name_type\":\"district\",\"state_name_type\":\"do_si\",\"label_overrides\":[{\"field\":\"BI\",\"message\":\"MSG_STREET_NUMBER\"},{\"field\":\"S2\",\"message\":\"MSG_NEIGHBORHOOD\"},{\"field\":\"S4\",\"message\":\"MSG_STREET_NAME\"}]}");
    map.put("KW", "{\"name\":\"KUWAIT\",\"fmt\":\"%N%n%O%n%A%n%Z %C\"}");
    map.put("KY", "{\"name\":\"CAYMAN ISLANDS\",\"lang\":\"en\",\"languages\":\"en\",\"fmt\":\"%N%n%O%n%A%n%S %Z\",\"require\":\"AS\",\"state_name_type\":\"island\"}");
    map.put("KZ", "{\"name\":\"KAZAKHSTAN\",\"fmt\":\"%Z%n%S%n%C%n%A%n%O%n%N\"}");
    map.put("LA", "{\"name\":\"LAO (PEOPLE'S DEM. REP.)\",\"fmt\":\"%N%n%O%n%A%n%Z %C\"}");
    map.put("LB", "{\"name\":\"LEBANON\",\"fmt\":\"%N%n%O%n%A%n%C %Z\"}");
    map.put("LC", "{\"name\":\"SAINT LUCIA\"}");
    map.put("LI", "{\"name\":\"LIECHTENSTEIN\",\"fmt\":\"%O%n%N%n%A%nFL-%Z %C\",\"require\":\"ACZ\",\"postprefix\":\"FL-\"}");
    map.put("LK", "{\"name\":\"SRI LANKA\",\"fmt\":\"%N%n%O%n%A%n%C%n%Z\"}");
    map.put("LR", "{\"name\":\"LIBERIA\",\"fmt\":\"%N%n%O%n%A%n%Z %C\"}");
    map.put("LS", "{\"name\":\"LESOTHO\",\"fmt\":\"%N%n%O%n%A%n%C %Z\"}");
    map.put("LT", "{\"name\":\"LITHUANIA\",\"fmt\":\"%O%n%N%n%A%nLT-%Z %C\",\"require\":\"ACZ\",\"postprefix\":\"LT-\"}");
    map.put("LU", "{\"name\":\"LUXEMBOURG\",\"fmt\":\"%O%n%N%n%A%nL-%Z %C\",\"require\":\"ACZ\",\"postprefix\":\"L-\"}");
    map.put("LV", "{\"name\":\"LATVIA\",\"fmt\":\"%N%n%O%n%A%n%C, %Z\",\"require\":\"ACZ\"}");
    map.put("LY", "{\"name\":\"LIBYA\"}");
    map.put("MA", "{\"name\":\"MOROCCO\",\"fmt\":\"%N%n%O%n%A%n%Z %C\"}");
    map.put("MC", "{\"name\":\"MONACO\",\"fmt\":\"%N%n%O%n%A%nMC-%Z %C %X\",\"postprefix\":\"MC-\"}");
    map.put("MD", "{\"name\":\"Rep. MOLDOVA\",\"fmt\":\"%N%n%O%n%A%nMD-%Z %C\",\"postprefix\":\"MD-\"}");
    map.put("ME", "{\"name\":\"MONTENEGRO\",\"fmt\":\"%N%n%O%n%A%n%Z %C\"}");
    map.put("MF", "{\"name\":\"SAINT MARTIN\",\"fmt\":\"%O%n%N%n%A%n%Z %C %X\",\"require\":\"ACZ\",\"upper\":\"ACX\"}");
    map.put("MG", "{\"name\":\"MADAGASCAR\",\"fmt\":\"%N%n%O%n%A%n%Z %C\"}");
    map.put("MH", "{\"name\":\"MARSHALL ISLANDS\",\"fmt\":\"%N%n%O%n%A%n%C %S %Z\",\"require\":\"ACSZ\",\"upper\":\"ACNOS\",\"state_name_type\":\"state\",\"zip_name_type\":\"zip\"}");
    map.put("MK", "{\"name\":\"MACEDONIA\",\"fmt\":\"%N%n%O%n%A%n%Z %C\"}");
    map.put("ML", "{\"name\":\"MALI\"}");
    map.put("MM", "{\"name\":\"MYANMAR\",\"fmt\":\"%N%n%O%n%A%n%C, %Z\"}");
    map.put("MN", "{\"name\":\"MONGOLIA\",\"fmt\":\"%N%n%O%n%A%n%C%n%S %Z\"}");
    map.put("MO", "{\"name\":\"MACAO\",\"lang\":\"zh-Hant\",\"languages\":\"zh-Hant\",\"lfmt\":\"%N%n%O%n%A\",\"fmt\":\"%A%n%O%n%N\",\"require\":\"A\"}");
    map.put("MP", "{\"name\":\"NORTHERN MARIANA ISLANDS\",\"fmt\":\"%N%n%O%n%A%n%C %S %Z\",\"require\":\"ACSZ\",\"upper\":\"ACNOS\",\"state_name_type\":\"state\",\"zip_name_type\":\"zip\"}");
    map.put("MQ", "{\"name\":\"MARTINIQUE\",\"fmt\":\"%O%n%N%n%A%n%Z %C %X\",\"require\":\"ACZ\",\"upper\":\"ACX\"}");
    map.put("MR", "{\"name\":\"MAURITANIA\",\"upper\":\"AC\"}");
    map.put("MS", "{\"name\":\"MONTSERRAT\"}");
    map.put("MT", "{\"name\":\"MALTA\",\"fmt\":\"%N%n%O%n%A%n%C %Z\",\"upper\":\"CZ\"}");
    map.put("MU", "{\"name\":\"MAURITIUS\",\"fmt\":\"%N%n%O%n%A%n%Z%n%C\",\"upper\":\"CZ\"}");
    map.put("MV", "{\"name\":\"MALDIVES\",\"fmt\":\"%N%n%O%n%A%n%C %Z\"}");
    map.put("MW", "{\"name\":\"MALAWI\",\"fmt\":\"%N%n%O%n%A%n%C %X\"}");
    map.put("MX", "{\"name\":\"MEXICO\",\"lang\":\"es\",\"languages\":\"es\",\"fmt\":\"%N%n%O%n%A%n%D%n%Z %C, %S\",\"require\":\"ACSZ\",\"upper\":\"CSZ\",\"sublocality_name_type\":\"neighborhood\",\"state_name_type\":\"state\",\"width_overrides\":\"%S:S\",\"label_overrides\":[{\"field\":\"S1\",\"label\":\"Delegación\"},{\"field\":\"S2\",\"label\":\"Supermanzana\"},{\"field\":\"S3\",\"label\":\"Manzana\"},{\"field\":\"LP\",\"label\":\"Lote\"}]}");
    map.put("MY", "{\"name\":\"MALAYSIA\",\"lang\":\"ms\",\"languages\":\"ms\",\"fmt\":\"%N%n%O%n%A%n%D%n%Z %C%n%S\",\"require\":\"ACZ\",\"upper\":\"CS\",\"sublocality_name_type\":\"village_township\",\"state_name_type\":\"state\"}");
    map.put("MZ", "{\"name\":\"MOZAMBIQUE\",\"lang\":\"pt\",\"languages\":\"pt\",\"fmt\":\"%N%n%O%n%A%n%Z %C%S\"}");
    map.put("NA", "{\"name\":\"NAMIBIA\",\"fmt\":\"%N%n%O%n%A%n%Cn%Z\"}");
    map.put("NC", "{\"name\":\"NEW CALEDONIA\",\"fmt\":\"%O%n%N%n%A%n%Z %C %X\",\"require\":\"ACZ\",\"upper\":\"ACX\"}");
    map.put("NE", "{\"name\":\"NIGER\",\"fmt\":\"%N%n%O%n%A%n%Z %C\"}");
    map.put("NF", "{\"name\":\"NORFOLK ISLAND\",\"fmt\":\"%O%n%N%n%A%n%C %S %Z\",\"upper\":\"CS\"}");
    map.put("NG", "{\"name\":\"NIGERIA\",\"lang\":\"en\",\"languages\":\"en\",\"fmt\":\"%N%n%O%n%A%n%D%n%C %Z%n%S\",\"upper\":\"CS\",\"state_name_type\":\"state\",\"label_overrides\":[{\"field\":\"D\",\"label\":\"Local government area\",\"lang\":\"en\"}]}");
    map.put("NI", "{\"name\":\"NICARAGUA\",\"lang\":\"es\",\"languages\":\"es\",\"fmt\":\"%N%n%O%n%A%n%Z%n%C, %S\",\"upper\":\"CS\",\"state_name_type\":\"department\"}");
    map.put("NL", "{\"name\":\"NETHERLANDS\",\"fmt\":\"%O%n%N%n%A%n%Z %C\",\"require\":\"ACZ\"}");
    map.put("NO", "{\"name\":\"NORWAY\",\"fmt\":\"%N%n%O%n%A%n%Z %C\",\"require\":\"ACZ\",\"locality_name_type\":\"post_town\"}");
    map.put("NP", "{\"name\":\"NEPAL\",\"fmt\":\"%N%n%O%n%A%n%C %Z\"}");
    map.put("NR", "{\"name\":\"NAURU CENTRAL PACIFIC\",\"lang\":\"en\",\"languages\":\"en\",\"fmt\":\"%N%n%O%n%A%n%S\",\"require\":\"AS\",\"state_name_type\":\"district\"}");
    map.put("NU", "{\"name\":\"NIUE\"}");
    map.put("NZ", "{\"name\":\"NEW ZEALAND\",\"fmt\":\"%N%n%O%n%A%n%D%n%C %Z\",\"require\":\"ACZ\"}");
    map.put("OM", "{\"name\":\"OMAN\",\"fmt\":\"%N%n%O%n%A%n%Z%n%C\"}");
    map.put("PA", "{\"name\":\"PANAMA (REP.)\",\"fmt\":\"%N%n%O%n%A%n%C%n%S\",\"upper\":\"CS\"}");
    map.put("PE", "{\"name\":\"PERU\",\"lang\":\"es\",\"languages\":\"es\",\"fmt\":\"%N%n%O%n%A%n%C %Z%n%S\",\"locality_name_type\":\"district\"}");
    map.put("PF", "{\"name\":\"FRENCH POLYNESIA\",\"fmt\":\"%N%n%O%n%A%n%Z %C %S\",\"require\":\"ACSZ\",\"upper\":\"CS\",\"state_name_type\":\"island\"}");
    map.put("PG", "{\"name\":\"PAPUA NEW GUINEA\",\"fmt\":\"%N%n%O%n%A%n%C %Z %S\",\"require\":\"ACS\"}");
    map.put("PH", "{\"name\":\"PHILIPPINES\",\"lang\":\"en\",\"languages\":\"en\",\"fmt\":\"%N%n%O%n%A%n%D, %C%n%Z %S\"}");
    map.put("PK", "{\"name\":\"PAKISTAN\",\"fmt\":\"%N%n%O%n%A%n%C-%Z\"}");
    map.put("PL", "{\"name\":\"POLAND\",\"fmt\":\"%N%n%O%n%A%n%Z %C\",\"require\":\"ACZ\"}");
    map.put("PM", "{\"name\":\"ST. PIERRE AND MIQUELON\",\"fmt\":\"%O%n%N%n%A%n%Z %C %X\",\"require\":\"ACZ\",\"upper\":\"ACX\"}");
    map.put("PN", "{\"name\":\"PITCAIRN\",\"fmt\":\"%N%n%O%n%A%n%C%n%Z\",\"require\":\"ACZ\",\"upper\":\"CZ\"}");
    map.put("PR", "{\"name\":\"PUERTO RICO\",\"fmt\":\"%N%n%O%n%A%n%C PR %Z\",\"require\":\"ACZ\",\"upper\":\"ACNO\",\"zip_name_type\":\"zip\",\"postprefix\":\"PR \"}");
    map.put("PS", "{\"name\":\"PALESTINIAN TERRITORY\"}");
    map.put("PT", "{\"name\":\"PORTUGAL\",\"fmt\":\"%N%n%O%n%A%n%Z %C\",\"require\":\"ACZ\"}");
    map.put("PW", "{\"name\":\"PALAU\",\"fmt\":\"%N%n%O%n%A%n%C %S %Z\",\"require\":\"ACSZ\",\"upper\":\"ACNOS\",\"state_name_type\":\"state\",\"zip_name_type\":\"zip\"}");
    map.put("PY", "{\"name\":\"PARAGUAY\",\"fmt\":\"%N%n%O%n%A%n%Z %C\"}");
    map.put("QA", "{\"name\":\"QATAR\",\"upper\":\"AC\"}");
    map.put("RE", "{\"name\":\"REUNION\",\"fmt\":\"%O%n%N%n%A%n%Z %C %X\",\"require\":\"ACZ\",\"upper\":\"ACX\"}");
    map.put("RO", "{\"name\":\"ROMANIA\",\"fmt\":\"%N%n%O%n%A%n%Z %C\",\"require\":\"ACZ\",\"upper\":\"AC\"}");
    map.put("RS", "{\"name\":\"REPUBLIC OF SERBIA\",\"fmt\":\"%N%n%O%n%A%n%Z %C\"}");
    map.put("RU", "{\"name\":\"RUSSIAN FEDERATION\",\"lang\":\"ru\",\"languages\":\"ru\",\"lfmt\":\"%N%n%O%n%A%n%C%n%S%n%Z\",\"fmt\":\"%N%n%O%n%A%n%C%n%S%n%Z\",\"require\":\"ACSZ\",\"upper\":\"AC\",\"state_name_type\":\"oblast\",\"label_overrides\":[{\"field\":\"CS\",\"message\":\"MSG_OFFICE_UNIT_NUMBER\"}]}");
    map.put("RW", "{\"name\":\"RWANDA\",\"upper\":\"AC\"}");
    map.put("SA", "{\"name\":\"SAUDI ARABIA\",\"fmt\":\"%N%n%O%n%A%n%C %Z\"}");
    map.put("SB", "{\"name\":\"SOLOMON ISLANDS\"}");
    map.put("SC", "{\"name\":\"SEYCHELLES\",\"fmt\":\"%N%n%O%n%A%n%C%n%S\",\"upper\":\"S\",\"state_name_type\":\"island\"}");
    map.put("SD", "{\"name\":\"SUDAN\",\"fmt\":\"%N%n%O%n%A%n%C%n%Z\",\"locality_name_type\":\"district\"}");
    map.put("SE", "{\"name\":\"SWEDEN\",\"fmt\":\"%O%n%N%n%A%nSE-%Z %C\",\"require\":\"ACZ\",\"locality_name_type\":\"post_town\",\"postprefix\":\"SE-\"}");
    map.put("SG", "{\"name\":\"REP. OF SINGAPORE\",\"fmt\":\"%N%n%O%n%A%nSINGAPORE %Z\",\"require\":\"AZ\"}");
    map.put("SH", "{\"name\":\"SAINT HELENA\",\"fmt\":\"%N%n%O%n%A%n%C%n%Z\",\"require\":\"ACZ\",\"upper\":\"CZ\"}");
    map.put("SI", "{\"name\":\"SLOVENIA\",\"fmt\":\"%N%n%O%n%A%nSI-%Z %C\",\"postprefix\":\"SI-\"}");
    map.put("SJ", "{\"name\":\"SVALBARD AND JAN MAYEN ISLANDS\",\"fmt\":\"%N%n%O%n%A%n%Z %C\",\"require\":\"ACZ\",\"locality_name_type\":\"post_town\"}");
    map.put("SK", "{\"name\":\"SLOVAKIA\",\"fmt\":\"%N%n%O%n%A%n%Z %C\",\"require\":\"ACZ\",\"label_overrides\":[{\"field\":\"NH\",\"label\":\"Obecní část\",\"lang\":\"cs\"},{\"field\":\"NH\",\"label\":\"Obecný časť\",\"lang\":\"sk\"},{\"field\":\"BI\",\"label\":\"Descriptive No.\"},{\"field\":\"BI\",\"label\":\"Popisné číslo\",\"lang\":\"cs\"},{\"field\":\"BI\",\"label\":\"Súpisné číslo\",\"lang\":\"sk\"},{\"field\":\"SN\",\"label\":\"Orientation No.\"},{\"field\":\"SN\",\"label\":\"Orientační číslo\",\"lang\":\"cs\"},{\"field\":\"SN\",\"label\":\"Orientačné číslo\",\"lang\":\"sk\"},{\"field\":\"S1\",\"label\":\"City District\"},{\"field\":\"S1\",\"label\":\"Městská část\",\"lang\":\"cs\"},{\"field\":\"S1\",\"label\":\"Mestská časť\",\"lang\":\"sk\"}]}");
    map.put("SL", "{\"name\":\"SIERRA LEONE\"}");
    map.put("SM", "{\"name\":\"SAN MARINO\",\"fmt\":\"%N%n%O%n%A%n%Z %C\",\"require\":\"AZ\"}");
    map.put("SN", "{\"name\":\"SENEGAL\",\"fmt\":\"%N%n%O%n%A%n%Z %C\"}");
    map.put("SO", "{\"name\":\"SOMALIA\",\"lang\":\"so\",\"languages\":\"so\",\"fmt\":\"%N%n%O%n%A%n%C, %S %Z\",\"require\":\"ACS\",\"upper\":\"ACS\"}");
    map.put("SR", "{\"name\":\"SURINAME\",\"lang\":\"nl\",\"languages\":\"nl\",\"fmt\":\"%N%n%O%n%A%n%C%n%S\",\"upper\":\"AS\"}");
    map.put("SS", "{\"name\":\"SOUTH SUDAN\"}");
    map.put("ST", "{\"name\":\"SAO TOME AND PRINCIPE\"}");
    map.put("SV", "{\"name\":\"EL SALVADOR\",\"lang\":\"es\",\"languages\":\"es\",\"fmt\":\"%N%n%O%n%A%n%Z-%C%n%S\",\"require\":\"ACS\",\"upper\":\"CSZ\"}");
    map.put("SX", "{\"name\":\"SINT MAARTEN\"}");
    map.put("SY", "{\"name\":\"SYRIA\",\"locality_name_type\":\"district\"}");
    map.put("SZ", "{\"name\":\"SWAZILAND\",\"fmt\":\"%N%n%O%n%A%n%C%n%Z\",\"upper\":\"ACZ\"}");
    map.put("TA", "{\"name\":\"TRISTAN DA CUNHA\",\"fmt\":\"%N%n%O%n%A%n%C%n%Z\"}");
    map.put("TC", "{\"name\":\"TURKS AND CAICOS ISLANDS\",\"fmt\":\"%N%n%O%n%A%n%C%n%Z\",\"require\":\"ACZ\",\"upper\":\"CZ\"}");
    map.put("TD", "{\"name\":\"CHAD\"}");
    map.put("TF", "{\"name\":\"FRENCH SOUTHERN TERRITORIES\"}");
    map.put("TG", "{\"name\":\"TOGO\"}");
    map.put("TH", "{\"name\":\"THAILAND\",\"lang\":\"th\",\"languages\":\"th\",\"lfmt\":\"%N%n%O%n%A%n%D, %C%n%S %Z\",\"fmt\":\"%N%n%O%n%A%n%D %C%n%S %Z\",\"upper\":\"S\",\"label_overrides\":[{\"field\":\"C\",\"label\":\"Amphoe / Khet\"},{\"field\":\"C\",\"label\":\"อำเภอ/เขต\",\"lang\":\"th\"},{\"field\":\"C\",\"label\":\"アムプー/ケート\",\"lang\":\"ja\"},{\"field\":\"C\",\"label\":\"암프/켓\",\"lang\":\"ko\"},{\"field\":\"C\",\"label\":\"郡/区\",\"lang\":\"zh\"},{\"field\":\"C\",\"label\":\"郡/區\",\"lang\":\"zh-TW\"},{\"field\":\"C\",\"label\":\"郡/區\",\"lang\":\"zh-HK\"},{\"field\":\"D\",\"label\":\"Tambon / Khwaeng\"},{\"field\":\"D\",\"label\":\"ตำบล/แขวง\",\"lang\":\"th\"},{\"field\":\"D\",\"label\":\"タムボン/クウェーン\",\"lang\":\"ja\"},{\"field\":\"D\",\"label\":\"땀본/쾡\",\"lang\":\"ko\"},{\"field\":\"D\",\"label\":\"区/小区\",\"lang\":\"zh\"},{\"field\":\"D\",\"label\":\"區/小區\",\"lang\":\"zh-TW\"},{\"field\":\"D\",\"label\":\"區/小區\",\"lang\":\"zh-HK\"}]}");
    map.put("TJ", "{\"name\":\"TAJIKISTAN\",\"fmt\":\"%N%n%O%n%A%n%Z %C\"}");
    map.put("TK", "{\"name\":\"TOKELAU\"}");
    map.put("TL", "{\"name\":\"TIMOR-LESTE\"}");
    map.put("TM", "{\"name\":\"TURKMENISTAN\",\"fmt\":\"%N%n%O%n%A%n%Z %C\"}");
    map.put("TN", "{\"name\":\"TUNISIA\",\"fmt\":\"%N%n%O%n%A%n%Z %C\"}");
    map.put("TO", "{\"name\":\"TONGA\"}");
    map.put("TR", "{\"name\":\"TURKEY\",\"lang\":\"tr\",\"languages\":\"tr\",\"fmt\":\"%N%n%O%n%A%n%Z %C/%S\",\"require\":\"ACZ\",\"locality_name_type\":\"district\",\"label_overrides\":[{\"field\":\"C\",\"label\":\"İlçe\",\"lang\":\"tr\"},{\"field\":\"S\",\"label\":\"İl\",\"lang\":\"tr\"},{\"field\":\"A4\",\"message\":\"MSG_NEIGHBORHOOD\"}]}");
    map.put("TT", "{\"name\":\"TRINIDAD AND TOBAGO\"}");
    map.put("TV", "{\"name\":\"TUVALU\",\"lang\":\"tyv\",\"languages\":\"tyv\",\"fmt\":\"%N%n%O%n%A%n%C%n%S\",\"upper\":\"ACS\",\"state_name_type\":\"island\"}");
    map.put("TW", "{\"name\":\"TAIWAN\",\"lang\":\"zh-Hant\",\"languages\":\"zh-Hant\",\"lfmt\":\"%N%n%O%n%A%n%C, %S %Z\",\"fmt\":\"%Z%n%S%C%n%A%n%O%n%N\",\"require\":\"ACSZ\",\"state_name_type\":\"county\"}");
    map.put("TZ", "{\"name\":\"TANZANIA (UNITED REP.)\",\"fmt\":\"%N%n%O%n%A%n%Z %C\"}");
    map.put("UA", "{\"name\":\"UKRAINE\",\"lang\":\"uk\",\"languages\":\"uk\",\"lfmt\":\"%N%n%O%n%A%n%C%n%S%n%Z\",\"fmt\":\"%N%n%O%n%A%n%C%n%S%n%Z\",\"require\":\"ACSZ\",\"state_name_type\":\"oblast\",\"label_overrides\":[{\"field\":\"CS\",\"message\":\"MSG_OFFICE_UNIT_NUMBER\"}]}");
    map.put("UG", "{\"name\":\"UGANDA\"}");
    map.put("UM", "{\"name\":\"UNITED STATES MINOR OUTLYING ISLANDS\",\"fmt\":\"%N%n%O%n%A%n%C %S %Z\",\"require\":\"ACS\",\"upper\":\"ACNOS\",\"state_name_type\":\"state\",\"zip_name_type\":\"zip\"}");
    map.put("US", "{\"name\":\"UNITED STATES\",\"lang\":\"en\",\"languages\":\"en\",\"fmt\":\"%N%n%O%n%A%n%C, %S %Z\",\"require\":\"ACSZ\",\"upper\":\"CS\",\"state_name_type\":\"state\",\"zip_name_type\":\"zip\",\"width_overrides\":\"%S:S\"}");
    map.put("UY", "{\"name\":\"URUGUAY\",\"lang\":\"es\",\"languages\":\"es\",\"fmt\":\"%N%n%O%n%A%n%Z %C %S\",\"upper\":\"CS\"}");
    map.put("UZ", "{\"name\":\"UZBEKISTAN\",\"fmt\":\"%N%n%O%n%A%n%Z %C%n%S\",\"upper\":\"CS\"}");
    map.put("VA", "{\"name\":\"VATICAN\",\"fmt\":\"%N%n%O%n%A%n%Z %C\"}");
    map.put("VC", "{\"name\":\"SAINT VINCENT AND THE GRENADINES (ANTILLES)\",\"fmt\":\"%N%n%O%n%A%n%C %Z\"}");
    map.put("VE", "{\"name\":\"VENEZUELA\",\"lang\":\"es\",\"languages\":\"es\",\"fmt\":\"%N%n%O%n%A%n%C %Z, %S\",\"require\":\"ACS\",\"upper\":\"CS\",\"state_name_type\":\"state\"}");
    map.put("VG", "{\"name\":\"VIRGIN ISLANDS (BRITISH)\",\"fmt\":\"%N%n%O%n%A%n%C%n%Z\",\"require\":\"A\"}");
    map.put("VI", "{\"name\":\"VIRGIN ISLANDS (U.S.)\",\"fmt\":\"%N%n%O%n%A%n%C %S %Z\",\"require\":\"ACSZ\",\"upper\":\"ACNOS\",\"state_name_type\":\"state\",\"zip_name_type\":\"zip\"}");
    map.put("VN", "{\"name\":\"VIET NAM\",\"lang\":\"vi\",\"languages\":\"vi\",\"lfmt\":\"%N%n%O%n%A%n%C%n%S %Z\",\"fmt\":\"%N%n%O%n%A%n%C%n%S %Z\",\"label_overrides\":[{\"field\":\"S1\",\"label\":\"Ward/Township/Commune\"},{\"field\":\"S1\",\"label\":\"Phường/Thị trấn/Xã\",\"lang\":\"vi\"}]}");
    map.put("VU", "{\"name\":\"VANUATU\"}");
    map.put("WF", "{\"name\":\"WALLIS AND FUTUNA ISLANDS\",\"fmt\":\"%O%n%N%n%A%n%Z %C %X\",\"require\":\"ACZ\",\"upper\":\"ACX\"}");
    map.put("WS", "{\"name\":\"SAMOA\"}");
    map.put("XK", "{\"name\":\"KOSOVO\",\"fmt\":\"%N%n%O%n%A%n%Z %C\"}");
    map.put("YE", "{\"name\":\"YEMEN\"}");
    map.put("YT", "{\"name\":\"MAYOTTE\",\"fmt\":\"%O%n%N%n%A%n%Z %C %X\",\"require\":\"ACZ\",\"upper\":\"ACX\"}");
    map.put("ZA", "{\"name\":\"SOUTH AFRICA\",\"fmt\":\"%N%n%O%n%A%n%D%n%C%n%Z\",\"require\":\"ACZ\"}");
    map.put("ZM", "{\"name\":\"ZAMBIA\",\"fmt\":\"%N%n%O%n%A%n%Z %C\"}");
    map.put("ZW", "{\"name\":\"ZIMBABWE\"}");
    map.put("ZZ", "{\"fmt\":\"%N%n%O%n%A%n%C\",\"require\":\"AC\",\"upper\":\"C\",\"sublocality_name_type\":\"suburb\",\"locality_name_type\":\"city\",\"state_name_type\":\"province\",\"zip_name_type\":\"postal\"}");
    return Collections.unmodifiableMap(map);
  }
}
