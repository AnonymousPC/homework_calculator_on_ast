#pragma once
#include "../string_class/basic_string.h"

#define templates            template < class string_type, class char_type >
#define string_algo          string_algo<string_type,char_type>
#define derive_of_self       static_cast<string_type&>(self)
#define const_derive_of_self static_cast<const string_type&>(self)

// Auxiliary

namespace aux
{
    map<std::text_encoding::id,std::string> encode_mapper =
    {
        { std::text_encoding::id::other,                   "other"                   },
        { std::text_encoding::id::unknown,                 "unknown"                 },
        { std::text_encoding::id::ASCII,                   "ASCII"                   },
        { std::text_encoding::id::ISOLatin1,               "ISOLatin1"               },
        { std::text_encoding::id::ISOLatin2,               "ISOLatin2"               },
        { std::text_encoding::id::ISOLatin3,               "ISOLatin3"               },
        { std::text_encoding::id::ISOLatin4,               "ISOLatin4"               },
        { std::text_encoding::id::ISOLatinCyrillic,        "ISOLatinCyrillic"        },
        { std::text_encoding::id::ISOLatinArabic,          "ISOLatinArabic"          },
        { std::text_encoding::id::ISOLatinGreek,           "ISOLatinGreek"           },
        { std::text_encoding::id::ISOLatinHebrew,          "ISOLatinHebrew"          },
        { std::text_encoding::id::ISOLatin5,               "ISOLatin5"               },
        { std::text_encoding::id::ISOLatin6,               "ISOLatin6"               },
        { std::text_encoding::id::ISOTextComm,             "ISOTextComm"             },
        { std::text_encoding::id::HalfWidthKatakana,       "HalfWidthKatakana"       },
        { std::text_encoding::id::JISEncoding,             "JISEncoding"             },
        { std::text_encoding::id::ShiftJIS,                "ShiftJIS"                },
        { std::text_encoding::id::EUCPkdFmtJapanese,       "EUCPkdFmtJapanese"       },
        { std::text_encoding::id::EUCFixWidJapanese,       "EUCFixWidJapanese"       },
        { std::text_encoding::id::ISO4UnitedKingdom,       "ISO4UnitedKingdom"       },
        { std::text_encoding::id::ISO11SwedishForNames,    "ISO11SwedishForNames"    },
        { std::text_encoding::id::ISO15Italian,            "ISO15Italian"            },
        { std::text_encoding::id::ISO17Spanish,            "ISO17Spanish"            },
        { std::text_encoding::id::ISO21German,             "ISO21German"             },
        { std::text_encoding::id::ISO60DanishNorwegian,    "ISO60DanishNorwegian"    },
        { std::text_encoding::id::ISO69French,             "ISO69French"             },
        { std::text_encoding::id::ISO10646UTF1,            "ISO10646UTF1"            },
        { std::text_encoding::id::ISO646basic1983,         "ISO646basic1983"         },
        { std::text_encoding::id::INVARIANT,               "INVARIANT"               },
        { std::text_encoding::id::ISO2IntlRefVersion,      "ISO2IntlRefVersion"      },
        { std::text_encoding::id::NATSSEFI,                "NATSSEFI"                },
        { std::text_encoding::id::NATSSEFIADD,             "NATSSEFIADD"             },
        { std::text_encoding::id::ISO10Swedish,            "ISO10Swedish"            },
        { std::text_encoding::id::KSC56011987,             "KSC56011987"             },
        { std::text_encoding::id::ISO2022KR,               "ISO2022KR"               },
        { std::text_encoding::id::EUCKR,                   "EUCKR"                   },
        { std::text_encoding::id::ISO2022JP,               "ISO2022JP"               },
        { std::text_encoding::id::ISO2022JP2,              "ISO2022JP2"              },
        { std::text_encoding::id::ISO13JISC6220jp,         "ISO13JISC6220jp"         },
        { std::text_encoding::id::ISO14JISC6220ro,         "ISO14JISC6220ro"         },
        { std::text_encoding::id::ISO16Portuguese,         "ISO16Portuguese"         },
        { std::text_encoding::id::ISO18Greek7Old,          "ISO18Greek7Old"          },
        { std::text_encoding::id::ISO19LatinGreek,         "ISO19LatinGreek"         },
        { std::text_encoding::id::ISO25French,             "ISO25French"             },
        { std::text_encoding::id::ISO27LatinGreek1,        "ISO27LatinGreek1"        },
        { std::text_encoding::id::ISO5427Cyrillic,         "ISO5427Cyrillic"         },
        { std::text_encoding::id::ISO42JISC62261978,       "ISO42JISC62261978"       },
        { std::text_encoding::id::ISO47BSViewdata,         "ISO47BSViewdata"         },
        { std::text_encoding::id::ISO49INIS,               "ISO49INIS"               },
        { std::text_encoding::id::ISO50INIS8,              "ISO50INIS8"              },
        { std::text_encoding::id::ISO51INISCyrillic,       "ISO51INISCyrillic"       },
        { std::text_encoding::id::ISO54271981,             "ISO54271981"             },
        { std::text_encoding::id::ISO5428Greek,            "ISO5428Greek"            },
        { std::text_encoding::id::ISO57GB1988,             "ISO57GB1988"             },
        { std::text_encoding::id::ISO58GB231280,           "ISO58GB231280"           },
        { std::text_encoding::id::ISO61Norwegian2,         "ISO61Norwegian2"         },
        { std::text_encoding::id::ISO70VideotexSupp1,      "ISO70VideotexSupp1"      },
        { std::text_encoding::id::ISO84Portuguese2,        "ISO84Portuguese2"        },
        { std::text_encoding::id::ISO85Spanish2,           "ISO85Spanish2"           },
        { std::text_encoding::id::ISO86Hungarian,          "ISO86Hungarian"          },
        { std::text_encoding::id::ISO87JISX0208,           "ISO87JISX0208"           },
        { std::text_encoding::id::ISO88Greek7,             "ISO88Greek7"             },
        { std::text_encoding::id::ISO89ASMO449,            "ISO89ASMO449"            },
        { std::text_encoding::id::ISO90,                   "ISO90"                   },
        { std::text_encoding::id::ISO91JISC62291984a,      "ISO91JISC62291984a"      },
        { std::text_encoding::id::ISO92JISC62991984b,      "ISO92JISC62991984b"      },
        { std::text_encoding::id::ISO93JIS62291984badd,    "ISO93JIS62291984badd"    },
        { std::text_encoding::id::ISO94JIS62291984hand,    "ISO94JIS62291984hand"    },
        { std::text_encoding::id::ISO95JIS62291984handadd, "ISO95JIS62291984handadd" },
        { std::text_encoding::id::ISO96JISC62291984kana,   "ISO96JISC62291984kana"   },
        { std::text_encoding::id::ISO2033,                 "ISO2033"                 },
        { std::text_encoding::id::ISO99NAPLPS,             "ISO99NAPLPS"             },
        { std::text_encoding::id::ISO102T617bit,           "ISO102T617bit"           },
        { std::text_encoding::id::ISO103T618bit,           "ISO103T618bit"           },
        { std::text_encoding::id::ISO111ECMACyrillic,      "ISO111ECMACyrillic"      },
        { std::text_encoding::id::ISO121Canadian1,         "ISO121Canadian1"         },
        { std::text_encoding::id::ISO122Canadian2,         "ISO122Canadian2"         },
        { std::text_encoding::id::ISO123CSAZ24341985gr,    "ISO123CSAZ24341985gr"    },
        { std::text_encoding::id::ISO88596E,               "ISO88596E"               },
        { std::text_encoding::id::ISO88596I,               "ISO88596I"               },
        { std::text_encoding::id::ISO128T101G2,            "ISO128T101G2"            },
        { std::text_encoding::id::ISO88598E,               "ISO88598E"               },
        { std::text_encoding::id::ISO88598I,               "ISO88598I"               },
        { std::text_encoding::id::ISO139CSN369103,         "ISO139CSN369103"         },
        { std::text_encoding::id::ISO141JUSIB1002,         "ISO141JUSIB1002"         },
        { std::text_encoding::id::ISO143IECP271,           "ISO143IECP271"           },
        { std::text_encoding::id::ISO146Serbian,           "ISO146Serbian"           },
        { std::text_encoding::id::ISO147Macedonian,        "ISO147Macedonian"        },
        { std::text_encoding::id::ISO150,                  "ISO150"                  },
        { std::text_encoding::id::ISO151Cuba,              "ISO151Cuba"              },
        { std::text_encoding::id::ISO6937Add,              "ISO6937Add"              },
        { std::text_encoding::id::ISO153GOST1976874,       "ISO153GOST1976874"       },
        { std::text_encoding::id::ISO8859Supp,             "ISO8859Supp"             },
        { std::text_encoding::id::ISO10367Box,             "ISO10367Box"             },
        { std::text_encoding::id::ISO158Lap,               "ISO158Lap"               },
        { std::text_encoding::id::ISO159JISX02121990,      "ISO159JISX02121990"      },
        { std::text_encoding::id::ISO646Danish,            "ISO646Danish"            },
        { std::text_encoding::id::USDK,                    "USDK"                    },
        { std::text_encoding::id::DKUS,                    "DKUS"                    },
        { std::text_encoding::id::KSC5636,                 "KSC5636"                 },
        { std::text_encoding::id::Unicode11UTF7,           "Unicode11UTF7"           },
        { std::text_encoding::id::ISO2022CN,               "ISO2022CN"               },
        { std::text_encoding::id::ISO2022CNEXT,            "ISO2022CNEXT"            },
        { std::text_encoding::id::UTF8,                    "UTF8"                    },
        { std::text_encoding::id::ISO885913,               "ISO885913"               },
        { std::text_encoding::id::ISO885914,               "ISO885914"               },
        { std::text_encoding::id::ISO885915,               "ISO885915"               },
        { std::text_encoding::id::ISO885916,               "ISO885916"               },
        { std::text_encoding::id::GBK,                     "GBK"                     },
        { std::text_encoding::id::GB18030,                 "GB18030"                 },
        { std::text_encoding::id::OSDEBCDICDF0415,         "OSDEBCDICDF0415"         },
        { std::text_encoding::id::OSDEBCDICDF03IRV,        "OSDEBCDICDF03IRV"        },
        { std::text_encoding::id::OSDEBCDICDF041,          "OSDEBCDICDF041"          },
        { std::text_encoding::id::ISO115481,               "ISO115481"               },
        { std::text_encoding::id::KZ1048,                  "KZ1048"                  },
        { std::text_encoding::id::UCS2,                    "UCS2"                    },
        { std::text_encoding::id::UCS4,                    "UCS4"                    },
        { std::text_encoding::id::UnicodeASCII,            "UnicodeASCII"            },
        { std::text_encoding::id::UnicodeLatin1,           "UnicodeLatin1"           },
        { std::text_encoding::id::UnicodeJapanese,         "UnicodeJapanese"         },
        { std::text_encoding::id::UnicodeIBM1261,          "UnicodeIBM1261"          },
        { std::text_encoding::id::UnicodeIBM1268,          "UnicodeIBM1268"          },
        { std::text_encoding::id::UnicodeIBM1276,          "UnicodeIBM1276"          },
        { std::text_encoding::id::UnicodeIBM1264,          "UnicodeIBM1264"          },
        { std::text_encoding::id::UnicodeIBM1265,          "UnicodeIBM1265"          },
        { std::text_encoding::id::Unicode11,               "Unicode11"               },
        { std::text_encoding::id::SCSU,                    "SCSU"                    },
        { std::text_encoding::id::UTF7,                    "UTF7"                    },
        { std::text_encoding::id::UTF16BE,                 "UTF16BE"                 },
        { std::text_encoding::id::UTF16LE,                 "UTF16LE"                 },
        { std::text_encoding::id::UTF16,                   "UTF16"                   },
        { std::text_encoding::id::CESU8,                   "CESU8"                   },
        { std::text_encoding::id::UTF32,                   "UTF32"                   },
        { std::text_encoding::id::UTF32BE,                 "UTF32BE"                 },
        { std::text_encoding::id::UTF32LE,                 "UTF32LE"                 },
        { std::text_encoding::id::BOCU1,                   "BOCU1"                   },
        { std::text_encoding::id::UTF7IMAP,                "UTF7IMAP"                },
        { std::text_encoding::id::Windows30Latin1,         "Windows30Latin1"         },
        { std::text_encoding::id::Windows31Latin1,         "Windows31Latin1"         },
        { std::text_encoding::id::Windows31Latin2,         "Windows31Latin2"         },
        { std::text_encoding::id::Windows31Latin5,         "Windows31Latin5"         },
        { std::text_encoding::id::HPRoman8,                "HPRoman8"                },
        { std::text_encoding::id::AdobeStandardEncoding,   "AdobeStandardEncoding"   },
        { std::text_encoding::id::VenturaUS,               "VenturaUS"               },
        { std::text_encoding::id::VenturaInternational,    "VenturaInternational"    },
        { std::text_encoding::id::DECMCS,                  "DECMCS"                  },
        { std::text_encoding::id::PC850Multilingual,       "PC850Multilingual"       },
        { std::text_encoding::id::PC8DanishNorwegian,      "PC8DanishNorwegian"      },
        { std::text_encoding::id::PC862LatinHebrew,        "PC862LatinHebrew"        },
        { std::text_encoding::id::PC8Turkish,              "PC8Turkish"              },
        { std::text_encoding::id::IBMSymbols,              "IBMSymbols"              },
        { std::text_encoding::id::IBMThai,                 "IBMThai"                 },
        { std::text_encoding::id::HPLegal,                 "HPLegal"                 },
        { std::text_encoding::id::HPPiFont,                "HPPiFont"                },
        { std::text_encoding::id::HPMath8,                 "HPMath8"                 },
        { std::text_encoding::id::HPPSMath,                "HPPSMath"                },
        { std::text_encoding::id::HPDesktop,               "HPDesktop"               },
        { std::text_encoding::id::VenturaMath,             "VenturaMath"             },
        { std::text_encoding::id::MicrosoftPublishing,     "MicrosoftPublishing"     },
        { std::text_encoding::id::Windows31J,              "Windows31J"              },
        { std::text_encoding::id::GB2312,                  "GB2312"                  },
        { std::text_encoding::id::Big5,                    "Big5"                    },
        { std::text_encoding::id::Macintosh,               "Macintosh"               },
        { std::text_encoding::id::IBM037,                  "IBM037"                  },
        { std::text_encoding::id::IBM038,                  "IBM038"                  },
        { std::text_encoding::id::IBM273,                  "IBM273"                  },
        { std::text_encoding::id::IBM274,                  "IBM274"                  },
        { std::text_encoding::id::IBM275,                  "IBM275"                  },
        { std::text_encoding::id::IBM277,                  "IBM277"                  },
        { std::text_encoding::id::IBM278,                  "IBM278"                  },
        { std::text_encoding::id::IBM280,                  "IBM280"                  },
        { std::text_encoding::id::IBM281,                  "IBM281"                  },
        { std::text_encoding::id::IBM284,                  "IBM284"                  },
        { std::text_encoding::id::IBM285,                  "IBM285"                  },
        { std::text_encoding::id::IBM290,                  "IBM290"                  },
        { std::text_encoding::id::IBM297,                  "IBM297"                  },
        { std::text_encoding::id::IBM420,                  "IBM420"                  },
        { std::text_encoding::id::IBM423,                  "IBM423"                  },
        { std::text_encoding::id::IBM424,                  "IBM424"                  },
        { std::text_encoding::id::PC8CodePage437,          "PC8CodePage437"          },
        { std::text_encoding::id::IBM500,                  "IBM500"                  },
        { std::text_encoding::id::IBM851,                  "IBM851"                  },
        { std::text_encoding::id::PCp852,                  "PCp852"                  },
        { std::text_encoding::id::IBM855,                  "IBM855"                  },
        { std::text_encoding::id::IBM857,                  "IBM857"                  },
        { std::text_encoding::id::IBM860,                  "IBM860"                  },
        { std::text_encoding::id::IBM861,                  "IBM861"                  },
        { std::text_encoding::id::IBM863,                  "IBM863"                  },
        { std::text_encoding::id::IBM864,                  "IBM864"                  },
        { std::text_encoding::id::IBM865,                  "IBM865"                  },
        { std::text_encoding::id::IBM868,                  "IBM868"                  },
        { std::text_encoding::id::IBM869,                  "IBM869"                  },
        { std::text_encoding::id::IBM870,                  "IBM870"                  },
        { std::text_encoding::id::IBM871,                  "IBM871"                  },
        { std::text_encoding::id::IBM880,                  "IBM880"                  },
        { std::text_encoding::id::IBM891,                  "IBM891"                  },
        { std::text_encoding::id::IBM903,                  "IBM903"                  },
        { std::text_encoding::id::IBM904,                  "IBM904"                  },
        { std::text_encoding::id::IBM905,                  "IBM905"                  },
        { std::text_encoding::id::IBM918,                  "IBM918"                  },
        { std::text_encoding::id::IBM1026,                 "IBM1026"                 },
        { std::text_encoding::id::IBMEBCDICATDE,           "IBMEBCDICATDE"           },
        { std::text_encoding::id::EBCDICATDEA,             "EBCDICATDEA"             },
        { std::text_encoding::id::EBCDICCAFR,              "EBCDICCAFR"              },
        { std::text_encoding::id::EBCDICDKNO,              "EBCDICDKNO"              },
        { std::text_encoding::id::EBCDICDKNOA,             "EBCDICDKNOA"             },
        { std::text_encoding::id::EBCDICFISE,              "EBCDICFISE"              },
        { std::text_encoding::id::EBCDICFISEA,             "EBCDICFISEA"             },
        { std::text_encoding::id::EBCDICFR,                "EBCDICFR"                },
        { std::text_encoding::id::EBCDICIT,                "EBCDICIT"                },
        { std::text_encoding::id::EBCDICPT,                "EBCDICPT"                },
        { std::text_encoding::id::EBCDICES,                "EBCDICES"                },
        { std::text_encoding::id::EBCDICESA,               "EBCDICESA"               },
        { std::text_encoding::id::EBCDICESS,               "EBCDICESS"               },
        { std::text_encoding::id::EBCDICUK,                "EBCDICUK"                },
        { std::text_encoding::id::EBCDICUS,                "EBCDICUS"                },
        { std::text_encoding::id::Unknown8BiT,             "Unknown8BiT"             },
        { std::text_encoding::id::Mnemonic,                "Mnemonic"                },
        { std::text_encoding::id::Mnem,                    "Mnem"                    },
        { std::text_encoding::id::VISCII,                  "VISCII"                  },
        { std::text_encoding::id::VIQR,                    "VIQR"                    },
        { std::text_encoding::id::KOI8R,                   "KOI8R"                   },
        { std::text_encoding::id::HZGB2312,                "HZGB2312"                },
        { std::text_encoding::id::IBM866,                  "IBM866"                  },
        { std::text_encoding::id::PC775Baltic,             "PC775Baltic"             },
        { std::text_encoding::id::KOI8U,                   "KOI8U"                   },
        { std::text_encoding::id::IBM00858,                "IBM00858"                },
        { std::text_encoding::id::IBM00924,                "IBM00924"                },
        { std::text_encoding::id::IBM01140,                "IBM01140"                },
        { std::text_encoding::id::IBM01141,                "IBM01141"                },
        { std::text_encoding::id::IBM01142,                "IBM01142"                },
        { std::text_encoding::id::IBM01143,                "IBM01143"                },
        { std::text_encoding::id::IBM01144,                "IBM01144"                },
        { std::text_encoding::id::IBM01145,                "IBM01145"                },
        { std::text_encoding::id::IBM01146,                "IBM01146"                },
        { std::text_encoding::id::IBM01147,                "IBM01147"                },
        { std::text_encoding::id::IBM01148,                "IBM01148"                },
        { std::text_encoding::id::IBM01149,                "IBM01149"                },
        { std::text_encoding::id::Big5HKSCS,               "Big5HKSCS"               },
        { std::text_encoding::id::IBM1047,                 "IBM1047"                 },
        { std::text_encoding::id::PTCP154,                 "PTCP154"                 },
        { std::text_encoding::id::Amiga1251,               "Amiga1251"               },
        { std::text_encoding::id::KOI7switched,            "KOI7switched"            },
        { std::text_encoding::id::BRF,                     "BRF"                     },
        { std::text_encoding::id::TSCII,                   "TSCII"                   },
        { std::text_encoding::id::CP51932,                 "CP51932"                 },
        { std::text_encoding::id::windows874,              "windows874"              },
        { std::text_encoding::id::windows1250,             "windows1250"             },
        { std::text_encoding::id::windows1251,             "windows1251"             },
        { std::text_encoding::id::windows1252,             "windows1252"             },
        { std::text_encoding::id::windows1253,             "windows1253"             },
        { std::text_encoding::id::windows1254,             "windows1254"             },
        { std::text_encoding::id::windows1255,             "windows1255"             },
        { std::text_encoding::id::windows1256,             "windows1256"             },
        { std::text_encoding::id::windows1257,             "windows1257"             },
        { std::text_encoding::id::windows1258,             "windows1258"             },
        { std::text_encoding::id::TIS620,                  "TIS620"                  },
        { std::text_encoding::id::CP50220,                 "CP50220"                 }
    };
}



// Abbreviation

templates
constexpr int string_algo::size ( ) const
{
    return const_derive_of_self.size();
}

templates
constexpr bool string_algo::empty ( ) const
{
    return const_derive_of_self.empty();
}

templates
constexpr decltype(auto) string_algo::begin ( )
{
    return derive_of_self.begin();
}

templates
constexpr decltype(auto) string_algo::begin ( ) const
{
    return const_derive_of_self.begin();
}

templates
constexpr decltype(auto) string_algo::end ( )
{
    return derive_of_self.end();
}

templates
constexpr decltype(auto) string_algo::end ( ) const
{
    return const_derive_of_self.end();
}

templates
constexpr decltype(auto) string_algo::operator [] ( int pos )
{
    return derive_of_self [pos];
}

templates
constexpr decltype(auto) string_algo::operator [] ( int pos ) const
{
    return const_derive_of_self [pos];
}

// String algo

templates
constexpr bool string_algo::begins_with ( const string_view& str ) const
{
    return size() >= str.size() ? std::equal ( begin(), begin() + str.size(), str.begin(), str.end() ) otherwise false;
}

templates
constexpr string_type& string_algo::capitalize ( )
{
    if ( not empty() )
        self[1] = ap::upper ( self[1] );

    return derive_of_self;
}

templates
constexpr string_type& string_algo::center ( int len, char_type ch )
    requires ( not is_view )
{
    if ( len <= size() )
        return derive_of_self;
    else
    {
        int old_size    = size();
        int left_space  = ( len - old_size )     / 2;
        int right_space = ( len - old_size + 1 ) / 2;

        derive_of_self.resize ( len );

        std::copy_backward ( begin(), begin() + old_size, end() - right_space );
        std::fill_n        ( begin(),             left_space,  ch );
        std::fill_n        ( end() - right_space, right_space, ch );

        return derive_of_self;
    }
}

templates
constexpr string_type& string_algo::encode ( encode_type from, encode_type to )
    requires ( not is_view ) and std::same_as<char_type,char>
{
    try
    {
        return derive_of_self = string_type(boost::locale::conv::between(std::basic_string<char_type>(derive_of_self),
                                                                         aux::encode_mapper[to],
                                                                         aux::encode_mapper[from],
                                                                         boost::locale::conv::stop));
    }
    catch ( const boost::locale::conv::conversion_error& e )
    {
        throw encode_error("cannot encode string {} from {} into {}: [[from {}]] {}", const_derive_of_self, from, to, typeid(e), e.what());
    }
    catch ( const boost::locale::conv::invalid_charset_error& e )
    {
        throw encode_error("cannot encode string {} from {} into {}: [[from {}]] {}", const_derive_of_self, from, to, typeid(e), e.what());
    }
}

templates
constexpr bool string_algo::ends_with ( const string_view& str ) const
{
    if ( size() >= str.size() )
        return std::equal ( end() - str.size(), end(), str.begin(), str.end() );
    else
        return false;
}

templates
constexpr string_type& string_algo::expand_tabs ( int tabs )
    requires ( not is_view )
{
    return derive_of_self.replace ( '\t', string_type(tabs, ' ') );
}

templates
constexpr string_type& string_algo::format ( const auto&... args )
    requires ( not is_view ) and std::same_as<char_type,char> and ( ( std::formattable<decltype(args),char_type> or std::constructible_from<string_type,decltype(args)> ) and ... )
{
    try
    {
        let b = begin();
        let e = end();
        let explicit_mode = false;

        while ( true )
        {
            let p = std::find(b, e, '{');
            if ( p == e )
                explicit_mode = false;            // Default mode.
            else if ( std::isdigit(*(p+1)) )
                explicit_mode = true;             // Explicit mode.
            else if ( p+1 < e and *(p+1) != '{' )
                explicit_mode = false;            // Implicit mode.
            else
                { b = p + 2; continue; }          // "{{"
            break;
        }

        if ( explicit_mode )
            return derive_of_self = std::vformat(static_cast<const char*>("{0}" + derive_of_self), std::make_format_args("", make_const_ref(make_formattable(args))...)).c_str();

        else /* implicit_mode or default_mode */
            return derive_of_self = std::vformat(static_cast<const char*>(derive_of_self), std::make_format_args(make_const_ref(make_formattable(args))...)).c_str();
    }

    catch ( const std::format_error& e )
    {
        throw format_error("cannot format string \"{}\" with args {}: [[from {}]] {}", derive_of_self, tuple(string(typeid(args))...), typeid(e), e.what());
    }
}

templates
constexpr bool string_algo::is_alnum ( ) const
{
    return ap::is_alnum ( const_derive_of_self );
}

templates
constexpr bool string_algo::is_alpha ( ) const
{
    return ap::is_alpha ( const_derive_of_self );
}

templates
constexpr bool string_algo::is_ascii ( ) const
{
    return ap::is_ascii ( const_derive_of_self );
}

templates
constexpr bool string_algo::is_decimal ( ) const
{
    return ap::is_decimal ( const_derive_of_self );
}

templates
constexpr bool string_algo::is_digit ( ) const
{
    return ap::is_digit ( const_derive_of_self );
}

templates
constexpr bool string_algo::is_identifier ( ) const
{
    return ap::is_identifier ( const_derive_of_self );
}

templates
constexpr bool string_algo::is_lower ( ) const
{
    return ap::is_lower ( const_derive_of_self );
}

templates
constexpr bool string_algo::is_space ( ) const
{
    return ap::is_space ( const_derive_of_self );
}

templates
constexpr bool string_algo::is_title ( ) const
{
    return ap::is_title ( const_derive_of_self );
}

templates
constexpr bool string_algo::is_upper ( ) const
{
    return ap::is_upper ( const_derive_of_self );
}

templates
constexpr string_type& string_algo::join ( const auto& strings )
    requires ( not is_view and requires { string_view(*strings.begin()); } )
{
    if constexpr ( requires { strings.size(); } )
        return derive_of_self = strings
                              | std::views::transform([] (const auto& str) { return string_view(str); })
                              | std::views::join_with(derive_of_self)
                              | std::ranges::to<string_type>(std::accumulate(strings.begin(), strings.end(), 0, [] (const auto& result, const auto& str) { return result + string_view(str).size(); }) + size()*(strings.size()-1));
    else
        return derive_of_self = strings
                              | std::views::transform([] (const auto& str) { return string_view(str); })
                              | std::views::join_with(derive_of_self)
                              | std::ranges::to<string_type>();
}

templates
constexpr string_type& string_algo::left_justify ( int len, const string_view& ch )
    requires ( not is_view )
{
    #if debug
        if ( ch.size() != 1 )
            throw value_error("the fill character {} must be exactly one character long", ch);
    #endif

    if ( len <= size() )
        return derive_of_self;
    else
    {
        int old_size = size();
        derive_of_self.resize(len);
        derive_of_self[old_size+1,-1].fill(ch[1]);
        return derive_of_self;
    }
}

templates
constexpr string_type& string_algo::left_strip ( const string_view& chars )
    requires ( not is_view )
{
    int pos = derive_of_self.string_type::array_algo::find([&] (char_type ch) { return not chars.contains(ch); });

    return pos != 0 ? derive_of_self.erase ( 1, pos - 1 ) otherwise
                      derive_of_self.clear(); // Every letter matches.
}

templates
constexpr string_type& string_algo::lower ( )
{
    return derive_of_self.each ( ap::lower<char_type> );
}

templates
constexpr string_algo::array_of_views string_algo::partition ( const string_view& str )
{
    return const_cast<array_line<views>&&> ( const_cast<const string_algo&>(self).partition(str) );
}

templates
constexpr const string_algo::array_of_views string_algo::partition ( const string_view& str ) const
{
    int pos = find ( str );

    if ( pos != 0 )
        return { const_derive_of_self[1,pos-1], const_derive_of_self[pos,pos+str.size()-1], const_derive_of_self[pos+str.size(),size()] };
    else
        return { const_derive_of_self[1,-1], const_derive_of_self[1,0], const_derive_of_self[1,0] };
}



templates
constexpr string_algo::array_of_views string_algo::right_partition ( const string_view& str )
{
    return const_cast<array_line<views>&&> ( const_cast<const string_algo&>(self).right_partition(str) );
}

templates
constexpr const string_algo::array_of_views string_algo::right_partition ( const string_view& str ) const
{
    int pos = right_find ( str );

    if ( pos != 0 )
        return { const_derive_of_self[1,pos-1], const_derive_of_self[pos,pos+str.size()-1], const_derive_of_self[pos+str.size(),size()] };
    else
        return { const_derive_of_self[1,0], const_derive_of_self[1,0], const_derive_of_self[1,-1] };
}

templates
constexpr string_type& string_algo::right_justify ( int len, const string_view& ch )
    requires ( not is_view )
{
    #if debug
        if ( ch.size() != 1 )
            throw value_error("the fill character {} must be exactly one character long", ch);
    #endif

    if ( len <= size() )
        return derive_of_self;
    else
    {
        int old_size = size();
        derive_of_self.resize(len);
        derive_of_self[-old_size,-1] = derive_of_self[1,old_size];
        derive_of_self[1,-old_size-1].fill(ch[1]);

        return derive_of_self;
    }
}

templates
constexpr string_algo::array_of_views string_algo::right_split ( const string_view& str, int times )
{
    return const_cast<array_line<views>&&> ( const_cast<const string_algo&>(self).right_split(str,times) );
}

templates
constexpr const string_algo::array_of_views string_algo::right_split ( const string_view& str, int times ) const
{
    vector<int> edges = vector{1-str.size()}.push ( where(str) )
                                            .push ( size() + 1 );

    if ( times >= 0 and times < edges.size() - 1 )
        edges.erase ( 2, edges.size() - times - 1 );

    return array_line<views> ( edges.size() - 1, [&] ( int i ) { return const_derive_of_self[edges[i]+str.size(), edges[i+1]-1]; } );
}

templates
constexpr string_type& string_algo::right_strip ( const string_view& chars )
    requires ( not is_view )
{
    int pos = derive_of_self.string_type::array_algo::right_find([&] (char_type ch) { return not chars.contains(ch); });

    return pos != 0 ? derive_of_self.erase ( pos+1, -1 ) otherwise
                      derive_of_self.clear(); // All match to chars.
}

templates
constexpr string_algo::array_of_views string_algo::split ( const string_view& str, int times )
{
    return const_cast<array_line<views>&&> ( const_cast<const string_algo&>(self).split(str,times) );
}

templates
constexpr const string_algo::array_of_views string_algo::split ( const string_view& str, int times ) const
{
    vector<int> edges = vector{1-str.size()}.push ( where(str) )
                                            .push ( size() + 1 );

    if ( times >= 0 and times < edges.size() - 1 )
        edges.erase ( times + 2, -2 );

    return array_line<views> ( edges.size() - 1, [&] ( int i ) { return const_derive_of_self[edges[i]+str.size(), edges[i+1]-1]; } );
}

templates
constexpr string_algo::array_of_views string_algo::split_lines ( )
{
    return const_cast<array_line<views>&&> ( const_cast<const string_algo&>(self).split_lines() );
}

templates
constexpr const string_algo::array_of_views string_algo::split_lines ( ) const
{
    vector<int> edges = vector<int>().push   ( const_derive_of_self.string_type::array_algo::where([] (auto ch) { return ch == '\n' or ch == '\r' or ch == '\f'; }) )
                                     .unique ( [&] ( auto pos1, auto pos2 ) { return pos1 + 1 == pos2 and self[pos1] == '\r' and self[pos2] == '\n'; } )
                                     .insert ( 1, 0 );

    // Split_lines is different from split('\n') as the last line will be ignored if it is empty.
    // For example, "line1\nlinr2\n\n\n" will split_lines() into 4 parts, but split() into 5 parts.
    // Thus, if the last letter is '\n' then regard the last edge as final sign.
    if ( self[-1] != '\n' )
        edges.push ( size() + 1 );

    array_line<views> lines ( edges.size() - 1, [&] ( int i )
    {
        return const_derive_of_self [ ( i != 1 and
                                        i != edges.size() and
                                        self[edges[i]  ] == '\r' and
                                        self[edges[i]+1] == '\n' ) ?
                                      edges[i] + 2 otherwise edges[i] + 1, edges[i+1] - 1 ];
    } );

    return lines;
}

templates
constexpr bool string_algo::starts_with ( const string_view& str ) const
{
    return begins_with ( str );
}

templates
constexpr string_type& string_algo::strip ( const string_view& chars )
    requires ( not is_view )
{
    return derive_of_self.left_strip(chars).right_strip(chars);
}

templates
constexpr string_type& string_algo::swap_case ( )
{
    return derive_of_self.each ( [] ( char_type& ch )
    {
        if ( ap::is_lower(ch) )
            ch = ap::upper(ch);

        else if ( ap::is_upper(ch) )
            ch = ap::lower(ch);
    } );
}

templates
constexpr string_type& string_algo::title ( )
{
    let poses = derive_of_self.adjacent_where([] (auto ch1, auto ch2) { return not ap::is_alpha(ch1) and ap::is_alpha(ch2); })
                              .each([] (int& pos) { ++pos; });
    if ( not empty() )
        poses.insert(1, 1);

    self.lower();
    for ( int pos in poses )
        self[pos] = ap::upper ( self[pos] );

    return derive_of_self;
}

templates
constexpr string_type& string_algo::upper ( )
{
    return derive_of_self.transform ( ap::upper<char_type> );
}

templates
constexpr string_type& string_algo::zero_fill ( int len )
    requires ( not is_view )
{
    return derive_of_self.right_justify(len,'0');
}






// Array algo (update)

templates
constexpr bool string_algo::contains ( const string_view& str ) const
{
    return std::search ( begin(), end(), str.begin(), str.end() ) != end();
}

templates
constexpr int string_algo::count ( const string_view& str ) const
{
    int times = 0;
    for ( auto it = begin(); it != end() + 1; it++ )
    {
        it = std::search ( it, end(), str.begin(), str.end() );
        times++;
    }

    return times - 1;
}

templates
constexpr bool string_algo::exist ( const string_view& str ) const
{
    return std::search ( begin(), end(), str.begin(), str.end() ) != end();
}

templates
constexpr int string_algo::find ( const string_view& str ) const
{
    int pos = std::search ( begin(), end(), str.begin(), str.end() ) - begin() + 1;
    return pos <= size() ? pos otherwise 0;
}

templates
constexpr bool string_algo::none ( const string_view& str ) const
{
    return std::search ( begin(), end(), str.begin(), str.end() ) == end();
}

templates
constexpr string_type& string_algo::replace ( const string_view& from, const string_view& to )
    requires ( not is_view )
{
    int p = 1;

    while ( true )
    {
        int f = p + derive_of_self[p,-1].find(from) - 1;

        if ( f == p - 1 )
            break;
        else
        {
            derive_of_self.erase ( f, f + from.size() - 1 )
                          .insert( f, to );
            p = f + to.size();
        }
    }

    return derive_of_self;
}

templates
constexpr string_type& string_algo::remove ( const string_view& str )
    requires ( not is_view )
{
    int p = 1;

    while ( true )
    {
        int f = p + derive_of_self[p,-1].find(str) - 1;

        if ( f == p - 1 )
            break;
        else
            derive_of_self.erase ( f, f + str.size() - 1 );
    }

    return derive_of_self;
}

templates
constexpr int string_algo::right_find ( const string_view& str ) const
{
    int pos = size() - str.size() + 1;

    while ( pos != 0 )
    {
        if ( const_derive_of_self[pos,pos+str.size()-1] == str )
            return pos;
        pos--;
    }

    return 0;
}

templates
constexpr vector<int> string_algo::where ( const string_view& str ) const
{
    vector<int> poses;
    for ( auto it = begin(); it != end() + 1; it++ )
    {
        it = std::search ( it, end(), str.begin(), str.end() );
        if ( it != end() )
            poses.push ( it - begin() + 1 );
    }

    return poses;
}




// Regex

templates
constexpr bool string_algo::all ( const regex& rgx ) const
{
    return std::regex_match ( begin(), end(), rgx );
}

templates
constexpr bool string_algo::contains ( const regex& rgx ) const
{
    return std::regex_search ( begin(), end(), rgx );
}

templates
constexpr int string_algo::count ( const regex& rgx ) const
{
    return std::distance ( std::regex_iterator<const char_type*>(begin(), end(), rgx), std::regex_iterator<const char_type*>() );
}

templates
constexpr bool string_algo::exist ( const regex& rgx ) const
{
    return std::regex_search ( begin(), end(), rgx );
}

templates
constexpr string_algo::views string_algo::find ( const regex& rgx )
{
    return const_cast<views&&> ( const_cast<const string_algo&>(self).find(rgx) );
}

templates
constexpr const string_algo::views string_algo::find ( const regex& rgx ) const
{
    let mtc   = std::match_results<const char_type*>();
    let found = std::regex_search ( begin(), end(), mtc, rgx );
    return found ? const_derive_of_self[mtc.position()+1, mtc.position()+mtc.length()] otherwise const_derive_of_self[1,0];
}

templates
constexpr bool string_algo::match ( const regex& rgx ) const
{
    return std::regex_match ( begin(), end(), rgx );
}

templates
constexpr bool string_algo::none ( const regex& rgx ) const
{
    return not std::regex_search ( begin(), end(), rgx );
}

templates
constexpr string_type& string_algo::replace ( const regex& rgx, const string_view& str )
    requires ( not is_view )
{
    return derive_of_self = string_type ( std::regex_replace ( std::basic_string<char_type>(derive_of_self), rgx, std::basic_string<char_type>(str) ) );
}

templates
constexpr string_type& string_algo::remove ( const regex& rgx )
    requires ( not is_view )
{
    return derive_of_self = string_type ( std::regex_replace ( std::basic_string<char_type>(derive_of_self), rgx, std::basic_string<char_type>(0, '\0') ) );
}

templates
constexpr string_algo::views string_algo::right_find ( const regex& rgx )
{
    return const_cast<views&&> ( const_cast<const string_algo&>(self).right_find(rgx) );
}

templates
constexpr const string_algo::views string_algo::right_find ( const regex& rgx ) const
{
    let mtc = std::match_results<const char_type*>();
    for ( let it = std::regex_iterator<const char_type*>(begin(), end(), rgx); it != std::regex_iterator<const char_type*>(); ++it )
        mtc = *it;
    let found = not mtc.empty();
    return found ? const_derive_of_self[mtc.position()+1, mtc.position()+mtc.length()] otherwise const_derive_of_self[1,0];
}

templates
constexpr string_algo::array_of_views string_algo::split ( const regex& rgx )
{
    return const_cast<array_line<views>&&> ( const_cast<const string_algo&>(self).split(rgx) );
}

templates
constexpr const string_algo::array_of_views string_algo::split ( const regex& rgx ) const
{
    if ( rgx.mark_count() == 0 )
        throw regex_error("cannot split {} with regex {}: regex has not capture groups", const_derive_of_self, rgx);

    let mtc     = std::match_results<const char_type*>();
    let matched = std::regex_match ( begin(), end(), mtc, rgx );

    if ( not matched )
        throw regex_error("cannot split {} with regex {}: string is not matched with regex", const_derive_of_self, rgx);

    return mtc | std::views::drop     (1)
               | std::views::transform([this] (const auto& submtc) { return const_derive_of_self[submtc.first-self.begin()+1, submtc.second-self.begin()]; })
               | std::ranges::to<array_line<views>>();
}

templates
constexpr string_algo::array_of_views string_algo::where ( const regex& rgx )
{
    return const_cast<array_line<views>&&> ( const_cast<const string_algo&>(self).where(rgx) );
}

templates
constexpr const string_algo::array_of_views string_algo::where ( const regex& rgx ) const
{
    return std::views::iota     (std::regex_iterator<const char_type*>(begin(), end(), rgx), std::regex_iterator<const char_type*>())
         | std::views::transform([&] (const auto& mtc) { return const_derive_of_self[mtc->position()+1, mtc->position()+mtc->length()]; })
         | std::ranges::to<array_line<views>>();
}


// Strlen

templates
constexpr int string_algo::strlen ( const char_type* addr )
{
    let p = addr;
    while ( *p != char_type('\0') )
        ++p;

    return p - addr;
}





// Auxiliary

templates
constexpr decltype(auto) string_algo::make_const_ref ( const auto& item )
{
    return item;
}

templates
constexpr decltype(auto) string_algo::make_formattable ( const auto& item )
{
    if constexpr ( std::formattable<decltype(item),char_type> )
        return item;
    else
        return string_type(item);
}






/// Global


constexpr bool is_alnum ( char_type auto ch )
{
    return ( ch >= 'a' and ch <= 'z' ) or ( ch >= 'A' and ch <= 'Z' ) or ( ch >= '0' and ch <= '9' );
}

constexpr bool is_alpha ( char_type auto ch )
{
    return ( ch >= 'a' and ch <= 'z' ) or ( ch >= 'A' and ch <= 'Z' );
}

constexpr bool is_ascii ( char_type auto ch )
{
    return ch >= 0 and ch <= 127;
}

constexpr bool is_decimal ( char_type auto ch )
{
    return ( ch >= '0' and ch <= '9' ) or ch == '.';
}

constexpr bool is_digit ( char_type auto ch )
{
    return ch >= '0' and ch <= '9';
}

constexpr bool is_lower ( char_type auto ch )
{
    return ch >= 'a' and ch <= 'z';
}

constexpr bool is_space ( char_type auto ch )
{
    return ch == ' ' or ch == '\f' or ch == '\n' or ch == '\r' or ch == '\t' or ch == '\v';
}

constexpr bool is_upper ( char_type auto ch )
{
    return ch >= 'A' and ch <= 'Z';
}

constexpr auto lower ( char_type auto ch )
{
    using result_type = decltype(ch);

    if ( is_upper ( ch ) )
        return result_type ( ch + 'a' - 'A' );
    else
        return ch;
}

constexpr auto upper ( char_type auto ch )
{
    using result_type = decltype(ch);

    if ( is_lower ( ch ) )
        return result_type ( ch + 'A' - 'a' );
    else
        return ch;
}



constexpr bool is_alnum ( const string_type auto& str )
{
    auto view = basic_string_view ( str );
    return not view.empty() and std::all_of ( view.begin(), view.end(), [] ( auto ch ) { return ap::is_alnum(ch); } );
}

constexpr bool is_alpha ( const string_type auto& str )
{
    auto view = basic_string_view ( str );
    return not view.empty() and std::all_of ( view.begin(), view.end(), [] ( auto ch ) { return ap::is_alpha(ch); } );
}

constexpr bool is_ascii ( const string_type auto& str )
{
    auto view = basic_string_view ( str );
    return not view.empty() and std::all_of ( view.begin(), view.end(), [] ( auto ch ) { return ap::is_ascii(ch); } );
}

constexpr bool is_decimal ( const string_type auto& str )
{
    auto view = basic_string_view ( str );
    return not view.empty() and std::all_of ( view.begin(), view.end(), [] ( auto ch ) { return ap::is_decimal(ch); } )
                            and std::count  ( view.begin(), view.end(), '.' ) <= 1
                            and std::count  ( view.begin(), view.end(), '-' ) <= 1;
}

constexpr bool is_digit ( const string_type auto& str )
{
    auto view = basic_string_view ( str );
    return not view.empty() and std::all_of ( view.begin(), view.end(), [] ( auto ch ) { return ap::is_digit(ch); } );
}

constexpr bool is_identifier ( const string_type auto& str )
{
    auto view = basic_string_view ( str );
    return not view.empty() and std::all_of ( view.begin(), view.end(), [] ( auto ch ) { return ap::is_alnum(ch) or ch == '_'; } )
                            and ( is_alpha ( view[1] ) or view[1] == '_' );
}

constexpr bool is_lower ( const string_type auto& str )
{
    auto view = basic_string_view ( str );
    return not view.empty() and std::all_of ( view.begin(), view.end(), [] ( auto ch ) { return ap::is_lower(ch); } );
}

constexpr bool is_space ( const string_type auto& str )
{
    auto view = basic_string_view ( str );
    return not view.empty() and std::all_of ( view.begin(), view.end(), [] ( auto ch ) { return ap::is_space(ch); } );
}

constexpr bool is_title ( const string_type auto& str )
{
    auto view = basic_string_view ( str );

    return not view.empty() and std::adjacent_find ( view.begin(), view.end(), [] ( auto ch1, auto ch2 ) { return not ap::is_alnum(ch1) and ap::is_lower(ch2); } ) == view.end()
                            and std::any_of        ( view.begin(), view.end(), [] ( auto ch )            { return ap::is_upper(ch); } );
}

constexpr bool is_upper ( const string_type auto& str )
{
    auto view = basic_string_view ( str );
    return not view.empty() and std::all_of ( view.begin(), view.end(), [] ( auto ch ) { return ap::is_upper(ch); } );
}

constexpr auto lower ( const string_type auto& str )
{
    return basic_string(str).lower();
}

constexpr auto upper ( const string_type auto& str )
{
    return basic_string(str).upper();
}








#undef templates
#undef string_algo
#undef derive_of_self
#undef const_derive_of_self

