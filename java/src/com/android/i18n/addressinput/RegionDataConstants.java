/*
 * Copyright (C) 2010 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.android.i18n.addressinput;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.HashMap;
import java.util.Map;

/**
 * Initial data in JSON format for regions. This has some formatting information for some countries,
 * and a list of all the regions that the widget can support. Data has been sorted below for ease of
 * editing.
 */
final class RegionDataConstants {
  private static final Map<String, String> COUNTRY_FORMAT_MAP = new HashMap<String, String>();

  private enum RegionDataEnum {
    AC(new String[]{
      "name", "ASCENSION ISLAND",
    }),
    AD(new String[]{
      "name", "ANDORRA",
      "lang", "ca",
      "languages", "ca",
      "fmt", "%N%n%O%n%A%n%Z %C",
      "require", "A",
    }),
    AE(new String[]{
      "name", "UNITED ARAB EMIRATES",
      "lang", "ar",
      "languages", "ar",
      "fmt", "%N%n%O%n%A%n%S",
      "lfmt", "%N%n%O%n%A%n%S",
      "require", "A",
      "state_name_type", "emirate",
    }),
    AF(new String[]{
      "name", "AFGHANISTAN",
    }),
    AG(new String[]{
      "name", "ANTIGUA AND BARBUDA",
      "require", "A",
    }),
    AI(new String[]{
      "name", "ANGUILLA",
    }),
    AL(new String[]{
      "name", "ALBANIA",
    }),
    AM(new String[]{
      "name", "ARMENIA",
      "lang", "hy",
      "languages", "hy",
      "fmt", "%N%n%O%n%A%n%Z%n%C%n%S",
      "lfmt", "%N%n%O%n%A%n%Z%n%C%n%S",
    }),
    AO(new String[]{
      "name", "ANGOLA",
    }),
    AQ(new String[]{
      "name", "ANTARCTICA",
    }),
    AR(new String[]{
      "name", "ARGENTINA",
      "lang", "es",
      "languages", "es",
      "fmt", "%N%n%O%n%A%n%Z %C%n%S",
      "upper", "ACZ",
      "state_name_type", "state",
    }),
    AS(new String[]{
      "name", "AMERICAN SAMOA",
      "fmt", "%N%n%O%n%A%n%C %S %Z",
      "require", "ACSZ",
      "upper", "ACNOS",
      "zip_name_type", "zip",
      "state_name_type", "state",
    }),
    AT(new String[]{
      "name", "AUSTRIA",
      "fmt", "%O%n%N%n%A%n%Z %C",
      "require", "ACZ",
    }),
    AU(new String[]{
      "name", "AUSTRALIA",
      "lang", "en",
      "languages", "en",
      "fmt", "%O%n%N%n%A%n%C %S %Z",
      "require", "ACSZ",
      "upper", "CS",
      "state_name_type", "state",
    }),
    AW(new String[]{
      "name", "ARUBA",
    }),
    AX(new String[]{
      "name", "FINLAND",
      "fmt", "%O%n%N%n%A%nAX-%Z %C%n\u00C5LAND",
      "require", "ACZ",
      "postprefix", "AX-",
    }),
    AZ(new String[]{
      "name", "AZERBAIJAN",
      "fmt", "%N%n%O%n%A%nAZ %Z %C",
      "postprefix", "AZ ",
    }),
    BA(new String[]{
      "name", "BOSNIA AND HERZEGOVINA",
      "fmt", "%N%n%O%n%A%n%Z %C",
    }),
    BB(new String[]{
      "name", "BARBADOS",
      "state_name_type", "parish",
    }),
    BD(new String[]{
      "name", "BANGLADESH",
      "fmt", "%N%n%O%n%A%n%C - %Z",
    }),
    BE(new String[]{
      "name", "BELGIUM",
      "fmt", "%O%n%N%n%A%n%Z %C",
      "require", "ACZ",
    }),
    BF(new String[]{
      "name", "BURKINA FASO",
      "fmt", "%N%n%O%n%A%n%C %X",
    }),
    BG(new String[]{
      "name", "BULGARIA (REP.)",
      "fmt", "%N%n%O%n%A%n%Z %C",
    }),
    BH(new String[]{
      "name", "BAHRAIN",
      "fmt", "%N%n%O%n%A%n%C %Z",
    }),
    BI(new String[]{
      "name", "BURUNDI",
    }),
    BJ(new String[]{
      "name", "BENIN",
      "upper", "AC",
    }),
    BL(new String[]{
      "name", "SAINT BARTHELEMY",
      "fmt", "%O%n%N%n%A%n%Z %C %X",
      "upper", "ACX",
      "require", "ACZ",
    }),
    BM(new String[]{
      "name", "BERMUDA",
      "fmt", "%N%n%O%n%A%n%C %Z",
    }),
    BN(new String[]{
      "name", "BRUNEI DARUSSALAM",
      "fmt", "%N%n%O%n%A%n%C %Z",
    }),
    BO(new String[]{
      "name", "BOLIVIA",
      "upper", "AC",
    }),
    BQ(new String[]{
      "name", "BONAIRE, SINT EUSTATIUS, AND SABA",
    }),
    BR(new String[]{
      "name", "BRAZIL",
      "lang", "pt",
      "languages", "pt",
      "fmt", "%O%n%N%n%A%n%D%n%C-%S%n%Z",
      "require", "ASCZ",
      "upper", "CS",
      "state_name_type", "state",
      "sublocality_name_type", "neighborhood",
    }),
    BS(new String[]{
      "name", "BAHAMAS",
      "lang", "en",
      "languages", "en",
      "fmt", "%N%n%O%n%A%n%C, %S",
      "state_name_type", "island",
    }),
    BT(new String[]{
      "name", "BHUTAN",
    }),
    BV(new String[]{
      "name", "BOUVET ISLAND",
    }),
    BW(new String[]{
      "name", "BOTSWANA",
    }),
    BY(new String[]{
      "name", "BELARUS",
      "fmt", "%S%n%Z %C %X%n%A%n%O%n%N",
    }),
    BZ(new String[]{
      "name", "BELIZE",
    }),
    CA(new String[]{
      "name", "CANADA",
      "lang", "en",
      "languages", "en~fr",
      "fmt", "%N%n%O%n%A%n%C %S %Z",
      "require", "ACSZ",
      "upper", "ACNOSZ",
    }),
    CC(new String[]{
      "name", "COCOS (KEELING) ISLANDS",
      "fmt", "%O%n%N%n%A%n%C %S %Z",
      "upper", "CS",
    }),
    CD(new String[]{
      "name", "CONGO (DEM. REP.)",
      "fmt", "%N%n%O%n%A%n%C %X",
    }),
    CF(new String[]{
      "name", "CENTRAL AFRICAN REPUBLIC",
    }),
    CG(new String[]{
      "name", "CONGO (REP.)",
    }),
    CH(new String[]{
      "name", "SWITZERLAND",
      "lang", "de",
      "languages", "de~fr~it",
      "fmt", "%O%n%N%n%A%nCH-%Z %C",
      "require", "ACZ",
      "upper", "",
      "postprefix", "CH-",
    }),
    CI(new String[]{
      "name", "COTE D'IVOIRE",
      "fmt", "%N%n%O%n%X %A %C %X",
    }),
    CK(new String[]{
      "name", "COOK ISLANDS",
    }),
    CL(new String[]{
      "name", "CHILE",
      "lang", "es",
      "languages", "es",
      "fmt", "%N%n%O%n%A%n%Z %C%n%S",
      "state_name_type", "state",
    }),
    CM(new String[]{
      "name", "CAMEROON",
    }),
    CN(new String[]{
      "name", "CHINA",
      "lang", "zh",
      "languages", "zh",
      "fmt", "%Z%n%S%C%D%n%A%n%O%n%N",
      "lfmt", "%N%n%O%n%A%n%D%n%C%n%S, %Z",
      "require", "ACSZ",
      "upper", "S",
      "sublocality_name_type", "district",
    }),
    CO(new String[]{
      "name", "COLOMBIA",
      "fmt", "%N%n%O%n%A%n%C, %S",
    }),
    CR(new String[]{
      "name", "COSTA RICA",
      "fmt", "%N%n%O%n%A%n%Z %C",
    }),
    CV(new String[]{
      "name", "CAPE VERDE",
      "lang", "pt",
      "languages", "pt",
      "fmt", "%N%n%O%n%A%n%Z %C%n%S",
      "state_name_type", "island",
    }),
    CW(new String[]{
      "name", "CURACAO",
    }),
    CX(new String[]{
      "name", "CHRISTMAS ISLAND",
      "fmt", "%O%n%N%n%A%n%C %S %Z",
      "upper", "CS",
    }),
    CY(new String[]{
      "name", "CYPRUS",
      "fmt", "%N%n%O%n%A%n%Z %C",
    }),
    CZ(new String[]{
      "name", "CZECH REP.",
      "fmt", "%N%n%O%n%A%n%Z %C",
    }),
    DE(new String[]{
      "name", "GERMANY",
      "fmt", "%N%n%O%n%A%n%Z %C",
      "require", "ACZ",
    }),
    DJ(new String[]{
      "name", "DJIBOUTI",
    }),
    DK(new String[]{
      "name", "DENMARK",
      "fmt", "%N%n%O%n%A%n%Z %C",
      "require", "ACZ",
    }),
    DM(new String[]{
      "name", "DOMINICA",
    }),
    DO(new String[]{
      "name", "DOMINICAN REP.",
      "fmt", "%N%n%O%n%A%n%Z %C",
    }),
    DZ(new String[]{
      "name", "ALGERIA",
      "fmt", "%N%n%O%n%A%n%Z %C",
    }),
    EC(new String[]{
      "name", "ECUADOR",
      "fmt", "%N%n%O%n%A%n%Z%n%C",
      "upper", "CZ",
    }),
    EE(new String[]{
      "name", "ESTONIA",
      "fmt", "%N%n%O%n%A%n%Z %C",
    }),
    EG(new String[]{
      "name", "EGYPT",
      "lang", "ar",
      "languages", "ar",
      "fmt", "%N%n%O%n%A%n%C%n%S%n%Z",
      "lfmt", "%N%n%O%n%A%n%C%n%S%n%Z",
    }),
    EH(new String[]{
      "name", "WESTERN SAHARA",
      "fmt", "%N%n%O%n%A%n%Z %C",
    }),
    ER(new String[]{
      "name", "ERITREA",
    }),
    ES(new String[]{
      "name", "SPAIN",
      "lang", "es",
      "languages", "es",
      "fmt", "%N%n%O%n%A%n%Z %C %S",
      "require", "ACSZ",
      "upper", "CS",
    }),
    ET(new String[]{
      "name", "ETHIOPIA",
      "fmt", "%N%n%O%n%A%n%Z %C",
    }),
    FI(new String[]{
      "name", "FINLAND",
      "fmt", "%O%n%N%n%A%nFI-%Z %C",
      "require", "ACZ",
      "postprefix", "FI-",
    }),
    FJ(new String[]{
      "name", "FIJI",
    }),
    FK(new String[]{
      "name", "FALKLAND ISLANDS (MALVINAS)",
      "fmt", "%N%n%O%n%A%n%X%n%C%n%Z",
      "require", "ACZ",
      "upper", "CZ",
    }),
    FM(new String[]{
      "name", "MICRONESIA (Federated State of)",
      "fmt", "%N%n%O%n%A%n%C %S %Z",
      "require", "ACSZ",
      "upper", "ACNOS",
      "zip_name_type", "zip",
      "state_name_type", "state",
    }),
    FO(new String[]{
      "name", "FAROE ISLANDS",
      "fmt", "%N%n%O%n%A%nFO%Z %C",
      "postprefix", "FO",
    }),
    FR(new String[]{
      "name", "FRANCE",
      "fmt", "%O%n%N%n%A%n%Z %C %X",
      "require", "ACZ",
      "upper", "CX",
    }),
    GA(new String[]{
      "name", "GABON",
    }),
    GB(new String[]{
      "name", "UNITED KINGDOM",
      "fmt", "%N%n%O%n%A%n%C%n%S%n%Z",
      "require", "ACZ",
      "upper", "CZ",
      "state_name_type", "county",
      "locality_name_type", "post_town",
    }),
    GD(new String[]{
      "name", "GRENADA (WEST INDIES)",
    }),
    GE(new String[]{
      "name", "GEORGIA",
      "fmt", "%N%n%O%n%A%n%Z %C",
    }),
    GF(new String[]{
      "name", "FRENCH GUIANA",
      "fmt", "%O%n%N%n%A%n%Z %C %X",
      "require", "ACZ",
      "upper", "ACX",
    }),
    GG(new String[]{
      "name", "CHANNEL ISLANDS",
      "fmt", "%N%n%O%n%A%n%X%n%C%nGUERNSEY%n%Z",
      "require", "ACZ",
      "upper", "CZ",
    }),
    GH(new String[]{
      "name", "GHANA",
    }),
    GI(new String[]{
      "name", "GIBRALTAR",
      "fmt", "%N%n%O%n%A%nGIBRALTAR%n%Z",
      "require", "A",
    }),
    GL(new String[]{
      "name", "GREENLAND",
      "fmt", "%N%n%O%n%A%n%Z %C",
      "require", "ACZ",
    }),
    GM(new String[]{
      "name", "GAMBIA",
    }),
    GN(new String[]{
      "name", "GUINEA",
      "fmt", "%N%n%O%n%Z %A %C",
    }),
    GP(new String[]{
      "name", "GUADELOUPE",
      "fmt", "%O%n%N%n%A%n%Z %C %X",
      "require", "ACZ",
      "upper", "ACX",
    }),
    GQ(new String[]{
      "name", "EQUATORIAL GUINEA",
    }),
    GR(new String[]{
      "name", "GREECE",
      "fmt", "%N%n%O%n%A%n%Z %C",
      "require", "ACZ",
    }),
    GS(new String[]{
      "name", "SOUTH GEORGIA",
      "fmt", "%N%n%O%n%A%n%X%n%C%n%Z",
      "require", "ACZ",
      "upper", "CZ",
    }),
    GT(new String[]{
      "name", "GUATEMALA",
      "fmt", "%N%n%O%n%A%n%Z- %C",
    }),
    GU(new String[]{
      "name", "GUAM",
      "fmt", "%N%n%O%n%A%n%C %S %Z",
      "require", "ACSZ",
      "upper", "ACNOS",
      "zip_name_type", "zip",
      "state_name_type", "state",
    }),
    GW(new String[]{
      "name", "GUINEA-BISSAU",
      "fmt", "%N%n%O%n%A%n%Z %C",
    }),
    GY(new String[]{
      "name", "GUYANA",
    }),
    HK(new String[]{
      "name", "HONG KONG",
      "lang", "zh-Hant",
      "languages", "zh-Hant~en",
      "fmt", "%S%n%C%n%A%n%O%n%N",
      "lfmt", "%N%n%O%n%A%n%C%n%S",
      "require", "AS",
      "upper", "S",
      "state_name_type", "area",
      "locality_name_type", "district",
    }),
    HM(new String[]{
      "name", "HEARD AND MCDONALD ISLANDS",
      "fmt", "%O%n%N%n%A%n%C %S %Z",
      "upper", "CS",
    }),
    HN(new String[]{
      "name", "HONDURAS",
      "fmt", "%N%n%O%n%A%n%C, %S%n%Z",
      "require", "ACS",
    }),
    HR(new String[]{
      "name", "CROATIA",
      "fmt", "%N%n%O%n%A%nHR-%Z %C",
      "postprefix", "HR-",
    }),
    HT(new String[]{
      "name", "HAITI",
      "fmt", "%N%n%O%n%A%nHT%Z %C %X",
      "postprefix", "HT",
    }),
    HU(new String[]{
      "name", "HUNGARY (Rep.)",
      "fmt", "%N%n%O%n%C%n%A%n%Z",
      "upper", "ACNO",
    }),
    ID(new String[]{
      "name", "INDONESIA",
      "lang", "id",
      "languages", "id",
      "fmt", "%N%n%O%n%A%n%C%n%S %Z",
    }),
    IE(new String[]{
      "name", "IRELAND",
      "lang", "en",
      "languages", "en",
      "fmt", "%N%n%O%n%A%n%C%n%S",
      "state_name_type", "county",
    }),
    IL(new String[]{
      "name", "ISRAEL",
      "fmt", "%N%n%O%n%A%n%C %Z",
    }),
    IM(new String[]{
      "name", "ISLE OF MAN",
      "fmt", "%N%n%O%n%A%n%X%n%C%n%Z",
      "require", "ACZ",
      "upper", "CZ",
    }),
    IN(new String[]{
      "name", "INDIA",
      "lang", "en",
      "languages", "en",
      "fmt", "%N%n%O%n%A%n%C %Z%n%S",
      "require", "ACSZ",
      "zip_name_type", "pin",
      "state_name_type", "state",
    }),
    IO(new String[]{
      "name", "BRITISH INDIAN OCEAN TERRITORY",
      "fmt", "%N%n%O%n%A%n%X%n%C%n%Z",
      "require", "ACZ",
      "upper", "CZ",
    }),
    IQ(new String[]{
      "name", "IRAQ",
      "fmt", "%O%n%N%n%A%n%C, %S%n%Z",
      "require", "ACS",
      "upper", "CS",
    }),
    IS(new String[]{
      "name", "ICELAND",
      "fmt", "%N%n%O%n%A%n%Z %C",
    }),
    IT(new String[]{
      "name", "ITALY",
      "lang", "it",
      "languages", "it",
      "fmt", "%N%n%O%n%A%n%Z %C %S",
      "require", "ACSZ",
      "upper", "CS",
    }),
    JE(new String[]{
      "name", "CHANNEL ISLANDS",
      "fmt", "%N%n%O%n%A%n%X%n%C%nJERSEY%n%Z",
      "require", "ACZ",
      "upper", "CZ",
    }),
    JM(new String[]{
      "name", "JAMAICA",
      "lang", "en",
      "languages", "en",
      "fmt", "%N%n%O%n%A%n%C%n%S %X",
      "require", "ACS",
      "state_name_type", "parish",
    }),
    JO(new String[]{
      "name", "JORDAN",
      "fmt", "%N%n%O%n%A%n%C %Z",
    }),
    JP(new String[]{
      "name", "JAPAN",
      "lang", "ja",
      "languages", "ja",
      "fmt", "\u3012%Z%n%S%C%n%A%n%O%n%N",
      "lfmt", "%N%n%O%n%A%n%C, %S%n%Z",
      "require", "ACSZ",
      "upper", "S",
      "state_name_type", "prefecture",
    }),
    KE(new String[]{
      "name", "KENYA",
      "fmt", "%N%n%O%n%A%n%C%n%Z",
    }),
    KG(new String[]{
      "name", "KYRGYZSTAN",
      "fmt", "%Z %C %X%n%A%n%O%n%N",
    }),
    KH(new String[]{
      "name", "CAMBODIA",
      "fmt", "%N%n%O%n%A%n%C %Z",
    }),
    KI(new String[]{
      "name", "KIRIBATI",
      "fmt", "%N%n%O%n%A%n%S%n%C",
      "upper", "ACNOS",
      "state_name_type", "island",
    }),
    KM(new String[]{
      "name", "COMOROS",
      "upper", "AC",
    }),
    KN(new String[]{
      "name", "SAINT KITTS AND NEVIS",
      "lang", "en",
      "languages", "en",
      "fmt", "%N%n%O%n%A%n%C, %S",
      "require", "ACS",
      "state_name_type", "island",
    }),
    KR(new String[]{
      "name", "KOREA (REP.)",
      "lang", "ko",
      "languages", "ko",
      "fmt", "%S %C%D%n%A%n%O%n%N%n%Z",
      "lfmt", "%N%n%O%n%A%n%D%n%C%n%S%n%Z",
      "require", "ACSZ",
      "upper", "Z",
      "state_name_type", "do_si",
      "sublocality_name_type", "district",
    }),
    KW(new String[]{
      "name", "KUWAIT",
      "fmt", "%N%n%O%n%A%n%Z %C",
    }),
    KY(new String[]{
      "name", "CAYMAN ISLANDS",
      "lang", "en",
      "languages", "en",
      "fmt", "%N%n%O%n%A%n%S %Z",
      "require", "AS",
      "state_name_type", "island",
    }),
    KZ(new String[]{
      "name", "KAZAKHSTAN",
      "fmt", "%Z%n%S%n%C%n%A%n%O%n%N",
    }),
    LA(new String[]{
      "name", "LAO (PEOPLE'S DEM. REP.)",
      "fmt", "%N%n%O%n%A%n%Z %C",
    }),
    LB(new String[]{
      "name", "LEBANON",
      "fmt", "%N%n%O%n%A%n%C %Z",
    }),
    LC(new String[]{
      "name", "SAINT LUCIA",
    }),
    LI(new String[]{
      "name", "LIECHTENSTEIN",
      "fmt", "%O%n%N%n%A%nFL-%Z %C",
      "require", "ACZ",
      "postprefix", "FL-",
    }),
    LK(new String[]{
      "name", "SRI LANKA",
      "fmt", "%N%n%O%n%A%n%C%n%Z",
    }),
    LR(new String[]{
      "name", "LIBERIA",
      "fmt", "%N%n%O%n%A%n%Z %C %X",
    }),
    LS(new String[]{
      "name", "LESOTHO",
      "fmt", "%N%n%O%n%A%n%C %Z",
    }),
    LT(new String[]{
      "name", "LITHUANIA",
      "fmt", "%O%n%N%n%A%nLT-%Z %C",
      "postprefix", "LT-",
    }),
    LU(new String[]{
      "name", "LUXEMBOURG",
      "fmt", "%O%n%N%n%A%nL-%Z %C",
      "require", "ACZ",
      "postprefix", "L-",
    }),
    LV(new String[]{
      "name", "LATVIA",
      "fmt", "%N%n%O%n%A%n%C, %Z",
    }),
    LY(new String[]{
      "name", "LIBYA",
    }),
    MA(new String[]{
      "name", "MOROCCO",
      "fmt", "%N%n%O%n%A%n%Z %C",
    }),
    MC(new String[]{
      "name", "MONACO",
      "fmt", "%N%n%O%n%A%nMC-%Z %C %X",
      "postprefix", "MC-",
    }),
    MD(new String[]{
      "name", "Rep. MOLDOVA",
      "fmt", "%N%n%O%n%A%nMD-%Z %C",
      "postprefix", "MD-",
    }),
    ME(new String[]{
      "name", "MONTENEGRO",
      "fmt", "%N%n%O%n%A%n%Z %C",
    }),
    MF(new String[]{
      "name", "SAINT MARTIN",
      "fmt", "%O%n%N%n%A%n%Z %C %X",
      "upper", "ACX",
      "require", "ACZ",
    }),
    MG(new String[]{
      "name", "MADAGASCAR",
      "fmt", "%N%n%O%n%A%n%Z %C",
    }),
    MH(new String[]{
      "name", "MARSHALL ISLANDS",
      "fmt", "%N%n%O%n%A%n%C %S %Z",
      "require", "ACSZ",
      "upper", "ACNOS",
      "zip_name_type", "zip",
      "state_name_type", "state",
    }),
    MK(new String[]{
      "name", "MACEDONIA",
      "fmt", "%N%n%O%n%A%n%Z %C",
    }),
    ML(new String[]{
      "name", "MALI",
    }),
    MN(new String[]{
      "name", "MONGOLIA",
      "fmt", "%N%n%O%n%A%n%S %C-%X%n%Z",
    }),
    MO(new String[]{
      "name", "MACAO",
      "lang", "zh-Hant",
      "languages", "zh-Hant",
      "fmt", "%A%n%O%n%N",
      "lfmt", "%N%n%O%n%A",
      "require", "A",
    }),
    MP(new String[]{
      "name", "NORTHERN MARIANA ISLANDS",
      "fmt", "%N%n%O%n%A%n%C %S %Z",
      "require", "ACSZ",
      "upper", "ACNOS",
      "zip_name_type", "zip",
      "state_name_type", "state",
    }),
    MQ(new String[]{
      "name", "MARTINIQUE",
      "fmt", "%O%n%N%n%A%n%Z %C %X",
      "require", "ACZ",
      "upper", "ACX",
    }),
    MR(new String[]{
      "name", "MAURITANIA",
      "upper", "AC",
    }),
    MS(new String[]{
      "name", "MONTSERRAT",
    }),
    MT(new String[]{
      "name", "MALTA",
      "fmt", "%N%n%O%n%A%n%C %Z",
      "upper", "CZ",
    }),
    MU(new String[]{
      "name", "MAURITIUS",
      "fmt", "%N%n%O%n%A%n%Z%n%C",
      "upper", "CZ",
    }),
    MV(new String[]{
      "name", "MALDIVES",
      "fmt", "%N%n%O%n%A%n%C %Z",
    }),
    MW(new String[]{
      "name", "MALAWI",
      "fmt", "%N%n%O%n%A%n%C %X",
    }),
    MX(new String[]{
      "name", "MEXICO",
      "lang", "es",
      "languages", "es",
      "fmt", "%N%n%O%n%A%n%D%n%Z %C, %S",
      "require", "ACZ",
      "upper", "CSZ",
      "state_name_type", "state",
      "sublocality_name_type", "neighborhood",
    }),
    MY(new String[]{
      "name", "MALAYSIA",
      "lang", "ms",
      "languages", "ms",
      "fmt", "%N%n%O%n%A%n%D%n%Z %C%n%S",
      "require", "ACZ",
      "upper", "CS",
      "state_name_type", "state",
      "sublocality_name_type", "village_township",
    }),
    MZ(new String[]{
      "name", "MOZAMBIQUE",
    }),
    NA(new String[]{
      "name", "NAMIBIA",
    }),
    NC(new String[]{
      "name", "NEW CALEDONIA",
      "fmt", "%O%n%N%n%A%n%Z %C %X",
      "require", "ACZ",
      "upper", "ACX",
    }),
    NE(new String[]{
      "name", "NIGER",
      "fmt", "%N%n%O%n%A%n%Z %C",
    }),
    NF(new String[]{
      "name", "NORFOLK ISLAND",
      "fmt", "%O%n%N%n%A%n%C %S %Z",
      "upper", "CS",
    }),
    NG(new String[]{
      "name", "NIGERIA",
      "lang", "en",
      "languages", "en",
      "fmt", "%N%n%O%n%A%n%C %Z%n%S",
      "upper", "CS",
      "state_name_type", "state",
    }),
    NI(new String[]{
      "name", "NICARAGUA",
      "lang", "es",
      "languages", "es",
      "fmt", "%N%n%O%n%A%n%Z%n%C, %S",
      "upper", "CS",
      "state_name_type", "department",
    }),
    NL(new String[]{
      "name", "NETHERLANDS",
      "fmt", "%O%n%N%n%A%n%Z %C",
      "require", "ACZ",
    }),
    NO(new String[]{
      "name", "NORWAY",
      "fmt", "%N%n%O%n%A%n%Z %C",
      "require", "ACZ",
    }),
    NP(new String[]{
      "name", "NEPAL",
      "fmt", "%N%n%O%n%A%n%C %Z",
    }),
    NR(new String[]{
      "name", "NAURU CENTRAL PACIFIC",
      "lang", "en",
      "languages", "en",
      "fmt", "%N%n%O%n%A%n%S",
      "require", "AS",
      "state_name_type", "district",
    }),
    NU(new String[]{
      "name", "NIUE",
    }),
    NZ(new String[]{
      "name", "NEW ZEALAND",
      "fmt", "%N%n%O%n%A%n%D%n%C %Z",
      "require", "ACZ",
    }),
    OM(new String[]{
      "name", "OMAN",
      "fmt", "%N%n%O%n%A%n%Z%n%C",
    }),
    PA(new String[]{
      "name", "PANAMA (REP.)",
      "fmt", "%N%n%O%n%A%n%C%n%S",
      "upper", "CS",
    }),
    PE(new String[]{
      "name", "PERU",
    }),
    PF(new String[]{
      "name", "FRENCH POLYNESIA",
      "fmt", "%N%n%O%n%A%n%Z %C %S",
      "require", "ACSZ",
      "upper", "CS",
      "state_name_type", "island",
    }),
    PG(new String[]{
      "name", "PAPUA NEW GUINEA",
      "fmt", "%N%n%O%n%A%n%C %Z %S",
      "require", "ACS",
    }),
    PH(new String[]{
      "name", "PHILIPPINES",
      "lang", "en",
      "languages", "en",
      "fmt", "%N%n%O%n%A%n%D, %C%n%Z %S",
      "require", "AC",
    }),
    PK(new String[]{
      "name", "PAKISTAN",
      "fmt", "%N%n%O%n%A%n%C-%Z",
    }),
    PL(new String[]{
      "name", "POLAND",
      "fmt", "%N%n%O%n%A%n%Z %C",
      "require", "ACZ",
    }),
    PM(new String[]{
      "name", "ST. PIERRE AND MIQUELON",
      "fmt", "%O%n%N%n%A%n%Z %C %X",
      "require", "ACZ",
      "upper", "ACX",
    }),
    PN(new String[]{
      "name", "PITCAIRN",
      "fmt", "%N%n%O%n%A%n%X%n%C%n%Z",
      "require", "ACZ",
      "upper", "CZ",
    }),
    PR(new String[]{
      "name", "PUERTO RICO",
      "fmt", "%N%n%O%n%A%n%C PR %Z",
      "require", "ACZ",
      "upper", "ACNO",
      "zip_name_type", "zip",
      "postprefix", "PR",
    }),
    PS(new String[]{
      "name", "PALESTINIAN TERRITORY",
    }),
    PT(new String[]{
      "name", "PORTUGAL",
      "fmt", "%N%n%O%n%A%n%Z %C",
      "require", "ACZ",
    }),
    PW(new String[]{
      "name", "PALAU",
      "fmt", "%N%n%O%n%A%n%C %S %Z",
      "require", "ACSZ",
      "upper", "ACNOS",
      "zip_name_type", "zip",
      "state_name_type", "state",
    }),
    PY(new String[]{
      "name", "PARAGUAY",
      "fmt", "%N%n%O%n%A%n%Z %C",
    }),
    QA(new String[]{
      "name", "QATAR",
      "upper", "AC",
    }),
    RE(new String[]{
      "name", "REUNION",
      "fmt", "%O%n%N%n%A%n%Z %C %X",
      "require", "ACZ",
      "upper", "ACX",
    }),
    RO(new String[]{
      "name", "ROMANIA",
      "fmt", "%N%n%O%n%A%n%Z %C",
      "upper", "AC",
    }),
    RS(new String[]{
      "name", "REPUBLIC OF SERBIA",
      "fmt", "%N%n%O%n%A%n%Z %C",
    }),
    RU(new String[]{
      "name", "RUSSIAN FEDERATION",
      "lang", "ru",
      "languages", "ru",
      "fmt", "%N%n%O%n%A%n%C%n%S%n%Z",
      "lfmt", "%N%n%O%n%A%n%C%n%S%n%Z",
      "require", "ACZ",
      "upper", "AC",
      "state_name_type", "oblast",
    }),
    RW(new String[]{
      "name", "RWANDA",
      "upper", "AC",
    }),
    SA(new String[]{
      "name", "SAUDI ARABIA",
      "fmt", "%N%n%O%n%A%n%C %Z",
    }),
    SB(new String[]{
      "name", "SOLOMON ISLANDS",
    }),
    SC(new String[]{
      "name", "SEYCHELLES",
      "fmt", "%N%n%O%n%A%n%C%n%S",
      "upper", "S",
      "state_name_type", "island",
    }),
    SE(new String[]{
      "name", "SWEDEN",
      "fmt", "%O%n%N%n%A%nSE-%Z %C",
      "require", "ACZ",
      "postprefix", "SE-",
    }),
    SG(new String[]{
      "name", "REP. OF SINGAPORE",
      "fmt", "%N%n%O%n%A%nSINGAPORE %Z",
      "require", "AZ",
    }),
    SH(new String[]{
      "name", "SAINT HELENA",
      "fmt", "%N%n%O%n%A%n%X%n%C%n%Z",
      "require", "ACZ",
      "upper", "CZ",
    }),
    SI(new String[]{
      "name", "SLOVENIA",
      "fmt", "%N%n%O%n%A%nSI- %Z %C",
      "postprefix", "SI-",
    }),
    SJ(new String[]{
      "name", "SVALBARD AND JAN MAYEN ISLANDS",
      "fmt", "%N%n%O%n%A%n%Z %C",
      "require", "ACZ",
    }),
    SK(new String[]{
      "name", "SLOVAKIA",
      "fmt", "%N%n%O%n%A%n%Z %C",
    }),
    SL(new String[]{
      "name", "SIERRA LEONE",
    }),
    SM(new String[]{
      "name", "SAN MARINO",
      "fmt", "%N%n%O%n%A%n%Z %C",
      "require", "AZ",
    }),
    SN(new String[]{
      "name", "SENEGAL",
      "fmt", "%N%n%O%n%A%n%Z %C",
    }),
    SO(new String[]{
      "name", "SOMALIA",
      "lang", "so",
      "languages", "so",
      "fmt", "%N%n%O%n%A%n%C, %S %Z",
      "require", "ACS",
      "upper", "ACS",
    }),
    SR(new String[]{
      "name", "SURINAME",
      "lang", "nl",
      "languages", "nl",
      "fmt", "%N%n%O%n%A%n%C %X%n%S",
      "upper", "AS",
    }),
    ST(new String[]{
      "name", "SAO TOME AND PRINCIPE",
      "fmt", "%N%n%O%n%A%n%C %X",
    }),
    SV(new String[]{
      "name", "EL SALVADOR",
      "lang", "es",
      "languages", "es",
      "fmt", "%N%n%O%n%A%n%Z-%C%n%S",
      "require", "ACS",
      "upper", "CSZ",
    }),
    SX(new String[]{
      "name", "SINT MAARTEN"
    }),
    SZ(new String[]{
      "name", "SWAZILAND",
      "fmt", "%N%n%O%n%A%n%C%n%Z",
      "upper", "ACZ",
    }),
    TA(new String[]{
      "name", "TRISTAN DA CUNHA",
    }),
    TC(new String[]{
      "name", "TURKS AND CAICOS ISLANDS",
      "fmt", "%N%n%O%n%A%n%X%n%C%n%Z",
      "require", "ACZ",
      "upper", "CZ",
    }),
    TD(new String[]{
      "name", "CHAD",
    }),
    TF(new String[]{
      "name", "FRENCH SOUTHERN TERRITORIES",
    }),
    TG(new String[]{
      "name", "TOGO",
    }),
    TH(new String[]{
      "name", "THAILAND",
      "lang", "th",
      "languages", "th",
      "fmt", "%N%n%O%n%A%n%D %C%n%S %Z",
      "lfmt", "%N%n%O%n%A%n%D, %C%n%S %Z",
      "upper", "S",
    }),
    TJ(new String[]{
      "name", "TAJIKISTAN",
      "fmt", "%N%n%O%n%A%n%Z %C",
    }),
    TK(new String[]{
      "name", "TOKELAU",
    }),
    TL(new String[]{
      "name", "TIMOR-LESTE",
    }),
    TM(new String[]{
      "name", "TURKMENISTAN",
      "fmt", "%N%n%O%n%A%n%Z %C",
    }),
    TN(new String[]{
      "name", "TUNISIA",
      "fmt", "%N%n%O%n%A%n%Z %C",
    }),
    TO(new String[]{
      "name", "TONGA",
    }),
    TR(new String[]{
      "name", "TURKEY",
      "lang", "tr",
      "languages", "tr",
      "fmt", "%N%n%O%n%A%n%Z %C/%S",
      "require", "ACZ",
      "locality_name_type", "district",
    }),
    TT(new String[]{
      "name", "TRINIDAD AND TOBAGO",
    }),
    TV(new String[]{
      "name", "TUVALU",
      "lang", "tyv",
      "languages", "tyv",
      "fmt", "%N%n%O%n%A%n%X%n%C%n%S",
      "upper", "ACS",
      "state_name_type", "island",
    }),
    TW(new String[]{
      "name", "TAIWAN",
      "lang", "zh-Hant",
      "languages", "zh-Hant",
      "fmt", "%Z%n%S%C%n%A%n%O%n%N",
      "lfmt", "%N%n%O%n%A%n%C, %S %Z",
      "require", "ACSZ",
      "state_name_type", "county",
    }),
    TZ(new String[]{
      "name", "TANZANIA (UNITED REP.)",
    }),
    UA(new String[]{
      "lang", "uk",
      "languages", "uk",
      "name", "UKRAINE",
      "fmt", "%N%n%O%n%A%n%C%n%S%n%Z",
      "lfmt", "%N%n%O%n%A%n%C%n%S%n%Z",
      "require", "ACZ",
      "state_name_type", "oblast",
    }),
    UG(new String[]{
      "name", "UGANDA",
    }),
    UM(new String[]{
      "name", "UNITED STATES MINOR OUTLYING ISLANDS",
      "fmt", "%N%n%O%n%A%n%C %S %Z",
      "require", "ACS",
      "upper", "ACNOS",
      "zip_name_type", "zip",
      "state_name_type", "state",
    }),
    US(new String[]{
      "name", "UNITED STATES",
      "lang", "en",
      "languages", "en",
      "fmt", "%N%n%O%n%A%n%C, %S %Z",
      "require", "ACSZ",
      "upper", "CS",
      "zip_name_type", "zip",
      "state_name_type", "state",
    }),
    UY(new String[]{
      "name", "URUGUAY",
      "lang", "es",
      "languages", "es",
      "fmt", "%N%n%O%n%A%n%Z %C %S",
      "upper", "CS",
    }),
    UZ(new String[]{
      "name", "UZBEKISTAN",
      "fmt", "%N%n%O%n%A%n%Z %C%n%S",
      "upper", "CS",
    }),
    VA(new String[]{
      "name", "VATICAN",
      "fmt", "%N%n%O%n%A%n%Z %C",
    }),
    VC(new String[]{
      "name", "SAINT VINCENT AND THE GRENADINES (ANTILLES)",
    }),
    VE(new String[]{
      "name", "VENEZUELA",
      "lang", "es",
      "languages", "es",
      "fmt", "%N%n%O%n%A%n%C %Z, %S",
      "require", "ACS",
      "upper", "CS",
    }),
    VG(new String[]{
      "name", "VIRGIN ISLANDS (BRITISH)",
      "fmt", "%N%n%O%n%A%n%C%n%Z",
      "require", "A",
    }),
    VI(new String[]{
      "name", "VIRGIN ISLANDS (U.S.)",
      "fmt", "%N%n%O%n%A%n%C %S %Z",
      "require", "ACSZ",
      "upper", "ACNOS",
      "zip_name_type", "zip",
      "state_name_type", "state",
    }),
    VN(new String[]{
      "name", "VIET NAM",
      "lang", "vi",
      "languages", "vi",
      "fmt", "%N%n%O%n%A%n%C%n%S %Z",
      "lfmt", "%N%n%O%n%A%n%C%n%S %Z",
    }),
    VU(new String[]{
      "name", "VANUATU",
    }),
    WF(new String[]{
      "name", "WALLIS AND FUTUNA ISLANDS",
      "fmt", "%O%n%N%n%A%n%Z %C %X",
      "require", "ACZ",
      "upper", "ACX",
    }),
    WS(new String[]{
      "name", "SAMOA",
    }),
    XK(new String[]{
      "name", "KOSOVO",
      "fmt", "%N%n%O%n%A%n%Z %C",
    }),
    YE(new String[]{
      "name", "YEMEN",
    }),
    YT(new String[]{
      "name", "MAYOTTE",
      "fmt", "%O%n%N%n%A%n%Z %C %X",
      "require", "ACZ",
      "upper", "ACX",
    }),
    ZA(new String[]{
      "name", "SOUTH AFRICA",
      "fmt", "%N%n%O%n%A%n%D%n%C%n%Z",
      "require", "ACZ",
    }),
    ZM(new String[]{
      "name", "ZAMBIA",
      "fmt", "%N%n%O%n%A%n%Z %C",
    }),
    ZW(new String[]{
      "name", "ZIMBABWE",
    }),
    ZZ(new String[]{
      "fmt", "%N%n%O%n%A%n%C",
      "require", "AC",
      "upper", "C",
      "zip_name_type", "postal",
      "state_name_type", "province",
      "locality_name_type", "city",
      "sublocality_name_type", "suburb",
    });

    private String jsonString;

    private RegionDataEnum(String[] inputArray) {
      jsonString = convertArrayToJsonString(inputArray);
    }

    String getJsonString() {
      return jsonString;
    }
  }

  static {
    for (RegionDataEnum region : RegionDataEnum.values()) {
      COUNTRY_FORMAT_MAP.put(region.toString(), region.getJsonString());
    }
  }

  static Map<String, String> getCountryFormatMap() {
    return COUNTRY_FORMAT_MAP;
  }

  /**
   * Assumes the array is a well-formed array - i.e., there are no unmatched keys in the input.
   * Package-private so it can be accessed by tests.
   */
  static String convertArrayToJsonString(String[] input) {
    JSONObject object = new JSONObject();
    for (int i = 0; i < input.length; i += 2) {
      try {
        object.put(input[i], input[i + 1]);
      } catch (JSONException e) {
        // Ignore for now.
      }
    }
    return object.toString();
  }
}
