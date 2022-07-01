#pragma once

#include <iostream>
#include <string>
#include <vector>

enum FarsiArabicTashkeel_
{
    fat_FATHEH,
    fat_TANVIN_NASB,
    fat_ZAMMEH,
    fat_TANVIN_RAF,
    fat_KASREH,
    fat_TANVIN_JARR,
    fat_SOKOON,
    fat_TASHDID,
    fat_Tashkeel_Count
};

enum FarsiArabicTashkeel_ArabicNames_
{
    fat_FATHA = fat_FATHEH,
    fat_FATHA_TAN = fat_TANVIN_NASB,
    fat_DAMMA = fat_ZAMMEH,
    fat_DAMMA_TAN = fat_TANVIN_RAF,
    fat_KASRA = fat_KASREH,
    fat_KASRA_TAN = fat_TANVIN_JARR,
    fat_SUKUN = fat_SOKOON,
    fat_SHADDA = fat_TASHDID
};

enum FarsiArabicAlphabets_
{
    faa_ALEF_HAMZEH_ABOVE,     // أ
    faa_ALEF,                  // ا
    faa_ALEF_MAD_ABOVE,        // آ
    faa_HAMZEH,                // ء
    faa_VAAV_HAMZEH_ABOVE,     // ؤ
    faa_ALEF_HAMZEH_BELOW,     // إ
    faa_YEH_HAMZEH_ABOVE,      // ئ
    faa_BEH,                   // ب
    faa_PEH,                   // پ
    faa_TEH,                   // ت
    faa_TEH_TANIS,             // ة
    faa_SEH,                   // ث
    faa_JEEM,                  // ج
    faa_CHEH,                  // چ
    faa_HEH_JEEMY,             // ح
    faa_KHEH,                  // خ
    faa_DAAL,                  // د
    faa_ZAAL,                  // ذ
    faa_REH,                   // ر
    faa_ZEH,                   // ز
    faa_JEH,                   // ژ
    faa_SEEN,                  // س
    faa_SHEEN,                 // ش
    faa_SAAD,                  // ص
    faa_ZAAD,                  // ض
    faa_TAAH,                  // ط
    faa_ZAAH,                  // ظ
    faa_AIN,                   // ع
    faa_GHAIN,                 // غ
    faa_FEH,                   // ف
    faa_QAAF,                  // ق
    faa_KAAF,                  // ک
    faa_KAAF_NO_HEAD,          // ك
    faa_GAAF,                  // گ
    faa_LAAM,                  // ل
    faa_MEEM,                  // م
    faa_NOON,                  // ن
    faa_VAAV,                  // و
    faa_HEH,                   // ه
    faa_YEH,                   // ی
    faa_ARABIC_YEH,            // ي
    faa_ALEF_MAKSURA,          // ى
    faa_TATWEEL,               // ـ
    faa_LAAM_ALEF,             // لا
    faa_LAAM_ALEF_HAMZA_ABOVE, // لأ
};

enum FarsiArabicAlphabets_ArabicNames_
{
    faa_ALEF_HAMZA_ABOVE = faa_ALEF_HAMZEH_ABOVE,
    faa_ALEF_MADDA_ABOVE = faa_ALEF_MAD_ABOVE,
    faa_HAMZA = faa_HAMZEH,
    faa_WAAW_HAMZA_ABOVE = faa_VAAV_HAMZEH_ABOVE,
    faa_ALEF_HAMZA_BELOW = faa_ALEF_HAMZEH_BELOW,
    faa_YEH_HAMZA_ABOVE = faa_YEH_HAMZEH_ABOVE,
    faa_TEH_MARBUTA = faa_TEH_TANIS,
    faa_THEH = faa_SEH,
    faa_HAH = faa_HEH_JEEMY,
    faa_THAAL = faa_ZAAL,
    faa_ZAIN = faa_ZEH,
    faa_DAAD = faa_ZAAD,
    faa_KAAF_ARABIC = faa_KAAF_NO_HEAD,
    faa_KEHEH = faa_KAAF,
    faa_WAAW = faa_VAAV
};

enum FarsiArabicAlphabets_Forms_
{
    faa_Unicode,
    faa_Isolated,
    faa_Beginner,
    faa_Medium,
    faa_Final,
};

extern const std::vector<std::vector<std::string>> fa_AlphabetsAllForms;

namespace FarsiType
{
    /// <summary>Get Farsi/Arabic character place in a word for its form, depending its previous and next character.</summary>
    /// <param name="fa_character">Character you want to check its place.</param>
    /// <param name="prevFAChar">Previous character, to check if its connected to fa_character or not.</param>
    /// <param name="nextFAChar">Next character, to check if its connected to fa_character or not.</param>
    /// <returns>Returns an int in type of a char. Possible values: 0- no connection, 1- conntected from behind, 2- connected from front, 3- connected from both side.</returns>
    unsigned char GetFACharPlace(const std::string &fa_character, const std::string &prevFAChar, const std::string &nextFAChar);

    /// <summary>Check if given character is a Farsi/Arabic letter in beginner form or not.</summary>
    /// <param name="fa_character">Character you want to check.</param>
    /// <returns>Returns a bool value. Possible values: true, false.</returns>
    bool IsFACharBeginner(const std::string &fa_character);

    /// <summary>Find vector index of the give character in fa_AlphabetsAllForms vector</summary>
    /// <param name="fa_character">Character you want get its index.</param>
    /// <returns>Returns an int in type of a char. Possible values: 0 to 44 (fa_AlphabetsAllForms array size).</returns>
    unsigned char FindFACharIndex(const std::string &fa_character);

    /// <summary>Check if given character is a Farsi/Arabic letter or not.</summary>
    /// <param name="fa_character">Character you want to check.</param>
    /// <returns>Returns a bool value. Possible values: true, false.</returns>
    bool IsFAChar(const std::string &fa_character);

    /// <summary>Reverses Farsi/Arabic string and returns a vector of std::strings, each of them containing Farsi/Arabic letters with different byte counts.</summary>
    /// <param name="str">Farsi/Arabic string.</param>
    /// <returns>Returns a vector of std::strings.</returns>
    std::vector<std::string> ReverseFAText(const std::string &str);

    /// <summary>Get correct unicode of Farsi/Arabic letter depending on its position, previous, and next letters.</summary>
    /// <param name="fa_character">Character you want to check.</param>
    /// <param name="prevFAChar">Previous character, to check if its connected to fa_character or not.</param>
    /// <param name="nextFAChar">Next character, to check if its connected to fa_character or not.</param>
    /// <returns>Returns a std::string.</returns>
    std::string GetFACharGlyph(const std::string &fa_character, const std::string &prevFAChar, const std::string &nextFAChar);

    /// <summary>Converts a Farsi/Arabic string to a normal, fixed, not-reversed string for using it in you program :).</summary>
    /// <param name="text">Farsi/Arabic text.</param>
    /// <returns>Returns a std::string. Fixed Farsi/Arabic string</returns>
    std::string ConvertToFAGlyphs(const std::string &text);
    void FACodeList(int *codepoints);
    int FindFACharIndex(int codepoint);
    bool IsFAChar(int codepoint);
};

const std::vector<std::vector<std::string>> fa_AlphabetsAllForms =
    {
        {u8"\u0623", u8"\ufe83", u8"\u0623", u8"\ufe84", u8"\ufe84"}, // faa_ALEF_HAMZEH_ABOVE, // أ
        {u8"\u0627", u8"\ufe8d", u8"\u0627", u8"\ufe8e", u8"\ufe8e"}, // faa_ALEF, // ا
        {u8"\u0622", u8"\ufe81", u8"\u0622", u8"\ufe82", u8"\ufe82"}, // faa_ALEF_MAD_ABOVE, // آ
        {u8"\u0621", u8"\ufe80", u8"\u0621", u8"\u0621", u8"\u0621"}, // faa_HAMZA, // ء
        {u8"\u0624", u8"\ufe85", u8"\u0624", u8"\ufe86", u8"\ufe86"}, // faa_VAAV_HAMZEH_ABOVE, // ؤ
        {u8"\u0625", u8"\ufe87", u8"\u0625", u8"\ufe88", u8"\ufe88"}, // faa_ALEF_HAMZEH_BELOW, // إ
        {u8"\u0626", u8"\ufe89", u8"\ufe8b", u8"\ufe8c", u8"\ufe8a"}, // faa_YEH_HAMZEH_ABOVE, // ئ
        {u8"\u0628", u8"\ufe8f", u8"\ufe91", u8"\ufe92", u8"\ufe90"}, // faa_BEH, // ب
        {u8"\u067e", u8"\ufb56", u8"\ufb58", u8"\ufb59", u8"\ufb57"}, // faa_PEH, // پ
        {u8"\u062A", u8"\ufe95", u8"\ufe97", u8"\ufe98", u8"\ufe96"}, // faa_TEH, // ت
        {u8"\u0629", u8"\ufe93", u8"\u0629", u8"\u0629", u8"\ufe94"}, // faa_TEH_TANIS, // ة
        {u8"\u062b", u8"\ufe99", u8"\ufe9b", u8"\ufe9c", u8"\ufe9a"}, // faa_SEH, // ث
        {u8"\u062c", u8"\ufe9d", u8"\ufe9f", u8"\ufea0", u8"\ufe9e"}, // faa_JEEM, // ج
        {u8"\u0686", u8"\ufb7a", u8"\ufb7c", u8"\ufb7d", u8"\ufb7b"}, // faa_CHEH, // چ
        {u8"\u062d", u8"\ufea1", u8"\ufea3", u8"\ufea4", u8"\ufea2"}, // faa_HEH_JEEMY, // ح
        {u8"\u062e", u8"\ufea5", u8"\ufea7", u8"\ufea8", u8"\ufea6"}, // faa_KHEH, // خ
        {u8"\u062f", u8"\ufea9", u8"\u062f", u8"\ufeaa", u8"\ufeaa"}, // faa_DAAL, // د
        {u8"\u0630", u8"\ufeab", u8"\u0630", u8"\ufeac", u8"\ufeac"}, // faa_ZAAL, // ذ
        {u8"\u0631", u8"\ufead", u8"\u0631", u8"\ufeae", u8"\ufeae"}, // faa_REH, // ر
        {u8"\u0632", u8"\ufeaf", u8"\u0632", u8"\ufeb0", u8"\ufeb0"}, // faa_ZEH, // ز
        {u8"\u0698", u8"\ufb8a", u8"\u0698", u8"\ufb8b", u8"\ufb8b"}, // faa_JEH, // ژ
        {u8"\u0633", u8"\ufeb1", u8"\ufeb3", u8"\ufeb4", u8"\ufeb2"}, // faa_SEEN, // س
        {u8"\u0634", u8"\ufeb5", u8"\ufeb7", u8"\ufeb8", u8"\ufeb6"}, // faa_SHEEN, // ش
        {u8"\u0635", u8"\ufeb9", u8"\ufebb", u8"\ufebc", u8"\ufeba"}, // faa_SAAD, // ص
        {u8"\u0636", u8"\ufebd", u8"\ufebf", u8"\ufec0", u8"\ufebe"}, // faa_ZAAD, // ض
        {u8"\u0637", u8"\ufec1", u8"\ufec3", u8"\ufec4", u8"\ufec2"}, // faa_TAAH, // ط
        {u8"\u0638", u8"\ufec5", u8"\ufec7", u8"\ufec8", u8"\ufec6"}, // faa_ZAAH, // ظ
        {u8"\u0639", u8"\ufec9", u8"\ufecb", u8"\ufecc", u8"\ufeca"}, // faa_AIN, // ع
        {u8"\u063a", u8"\ufecd", u8"\ufecf", u8"\ufed0", u8"\ufece"}, // faa_GHAIN, // غ
        {u8"\u0641", u8"\ufed1", u8"\ufed3", u8"\ufed4", u8"\ufed2"}, // faa_FEH, // ف
        {u8"\u0642", u8"\ufed5", u8"\ufed7", u8"\ufed8", u8"\ufed6"}, // faa_QAAF, // ق
        {u8"\u06a9", u8"\ufed9", u8"\ufedb", u8"\ufedc", u8"\ufeda"}, // faa_KAAF, // ک // I had to change all forms to due to rendering issues in DX faa_KAAF_NO_HEAD | original: u8"\ufb8e", u8"\ufb90", u8"\ufb91", u8"\ufb8f"
        {u8"\u0643", u8"\ufed9", u8"\ufedb", u8"\ufedc", u8"\ufeda"}, // faa_KAAF_NO_HEAD, // ك
        {u8"\u06af", u8"\ufb92", u8"\ufb94", u8"\ufb95", u8"\ufb93"}, // faa_GAAF, // گ
        {u8"\u0644", u8"\ufedd", u8"\ufedf", u8"\ufee0", u8"\ufede"}, // faa_LAAM, // ل
        {u8"\u0645", u8"\ufee1", u8"\ufee3", u8"\ufee4", u8"\ufee2"}, // faa_MEEM, // م
        {u8"\u0646", u8"\ufee5", u8"\ufee7", u8"\ufee8", u8"\ufee6"}, // faa_NOON, // ن
        {u8"\u0647", u8"\ufee9", u8"\ufeeb", u8"\ufeec", u8"\ufeea"}, // faa_HEH, // ه
        {u8"\u0648", u8"\ufeed", u8"\ufeed", u8"\ufeee", u8"\ufeee"}, // faa_VAAV, // و
        {u8"\u06cc", u8"\ufbfc", u8"\ufbfe", u8"\ufbff", u8"\ufbfd"}, // faa_YEH, // ی
        {u8"\u064a", u8"\ufef1", u8"\ufef3", u8"\ufef4", u8"\ufef2"}, // faa_ARABIC_YEH, // ي
        {u8"\u0649", u8"\ufeef", u8"\u0649", u8"\ufef0", u8"\ufef0"}, // faa_ALEF_MAKSURA, // ى
        {u8"\u0640", u8"\u0640", u8"\u0640", u8"\u0640", u8"\u0640"}, // faa_TATWEEL, // ـ
        {u8"\ufefb", u8"\ufefb", u8"\ufefb", u8"\ufefc", u8"\ufefc"}, // faa_LAAM_ALEF, // لا
        {u8"\ufef7", u8"\ufef7", u8"\ufef7", u8"\ufef8", u8"\ufef8"}, // faa_LAAM_ALEF_HAMZA_ABOVE, // لأ
};
const std::vector<std::vector<int>> fa_AlphabetsAllFormsInt =
    {
        {0x0623, 0xfe83, 0x0623, 0xfe84, 0xfe84}, // faa_ALEF_HAMZEH_ABOVE, // أ
        {0x0627, 0xfe8d, 0x0627, 0xfe8e, 0xfe8e}, // faa_ALEF, // ا
        {0x0622, 0xfe81, 0x0622, 0xfe82, 0xfe82}, // faa_ALEF_MAD_ABOVE, // آ
        {0x0621, 0xfe80, 0x0621, 0x0621, 0x0621}, // faa_HAMZA, // ء
        {0x0624, 0xfe85, 0x0624, 0xfe86, 0xfe86}, // faa_VAAV_HAMZEH_ABOVE, // ؤ
        {0x0625, 0xfe87, 0x0625, 0xfe88, 0xfe88}, // faa_ALEF_HAMZEH_BELOW, // إ
        {0x0626, 0xfe89, 0xfe8b, 0xfe8c, 0xfe8a}, // faa_YEH_HAMZEH_ABOVE, // ئ
        {0x0628, 0xfe8f, 0xfe91, 0xfe92, 0xfe90}, // faa_BEH, // ب
        {0x067e, 0xfb56, 0xfb58, 0xfb59, 0xfb57}, // faa_PEH, // پ
        {0x062A, 0xfe95, 0xfe97, 0xfe98, 0xfe96}, // faa_TEH, // ت
        {0x0629, 0xfe93, 0x0629, 0x0629, 0xfe94}, // faa_TEH_TANIS, // ة
        {0x062b, 0xfe99, 0xfe9b, 0xfe9c, 0xfe9a}, // faa_SEH, // ث
        {0x062c, 0xfe9d, 0xfe9f, 0xfea0, 0xfe9e}, // faa_JEEM, // ج
        {0x0686, 0xfb7a, 0xfb7c, 0xfb7d, 0xfb7b}, // faa_CHEH, // چ
        {0x062d, 0xfea1, 0xfea3, 0xfea4, 0xfea2}, // faa_HEH_JEEMY, // ح
        {0x062e, 0xfea5, 0xfea7, 0xfea8, 0xfea6}, // faa_KHEH, // خ
        {0x062f, 0xfea9, 0x062f, 0xfeaa, 0xfeaa}, // faa_DAAL, // د
        {0x0630, 0xfeab, 0x0630, 0xfeac, 0xfeac}, // faa_ZAAL, // ذ
        {0x0631, 0xfead, 0x0631, 0xfeae, 0xfeae}, // faa_REH, // ر
        {0x0632, 0xfeaf, 0x0632, 0xfeb0, 0xfeb0}, // faa_ZEH, // ز
        {0x0698, 0xfb8a, 0x0698, 0xfb8b, 0xfb8b}, // faa_JEH, // ژ
        {0x0633, 0xfeb1, 0xfeb3, 0xfeb4, 0xfeb2}, // faa_SEEN, // س
        {0x0634, 0xfeb5, 0xfeb7, 0xfeb8, 0xfeb6}, // faa_SHEEN, // ش
        {0x0635, 0xfeb9, 0xfebb, 0xfebc, 0xfeba}, // faa_SAAD, // ص
        {0x0636, 0xfebd, 0xfebf, 0xfec0, 0xfebe}, // faa_ZAAD, // ض
        {0x0637, 0xfec1, 0xfec3, 0xfec4, 0xfec2}, // faa_TAAH, // ط
        {0x0638, 0xfec5, 0xfec7, 0xfec8, 0xfec6}, // faa_ZAAH, // ظ
        {0x0639, 0xfec9, 0xfecb, 0xfecc, 0xfeca}, // faa_AIN, // ع
        {0x063a, 0xfecd, 0xfecf, 0xfed0, 0xfece}, // faa_GHAIN, // غ
        {0x0641, 0xfed1, 0xfed3, 0xfed4, 0xfed2}, // faa_FEH, // ف
        {0x0642, 0xfed5, 0xfed7, 0xfed8, 0xfed6}, // faa_QAAF, // ق
        {0x06a9, 0xfed9, 0xfedb, 0xfedc, 0xfeda}, // faa_KAAF, // ک // I had to change all forms to due to rendering issues in DX faa_KAAF_NO_HEAD | original: 0xfb8e , 0xfb90 , 0xfb91 , 0xfb8f
        {0x0643, 0xfed9, 0xfedb, 0xfedc, 0xfeda}, // faa_KAAF_NO_HEAD, // ك
        {0x06af, 0xfb92, 0xfb94, 0xfb95, 0xfb93}, // faa_GAAF, // گ
        {0x0644, 0xfedd, 0xfedf, 0xfee0, 0xfede}, // faa_LAAM, // ل
        {0x0645, 0xfee1, 0xfee3, 0xfee4, 0xfee2}, // faa_MEEM, // م
        {0x0646, 0xfee5, 0xfee7, 0xfee8, 0xfee6}, // faa_NOON, // ن
        {0x0647, 0xfee9, 0xfeeb, 0xfeec, 0xfeea}, // faa_HEH, // ه
        {0x0648, 0xfeed, 0xfeed, 0xfeee, 0xfeee}, // faa_VAAV, // و
        {0x06cc, 0xfbfc, 0xfbfe, 0xfbff, 0xfbfd}, // faa_YEH, // ی
        {0x064a, 0xfef1, 0xfef3, 0xfef4, 0xfef2}, // faa_ARABIC_YEH, // ي
        {0x0649, 0xfeef, 0x0649, 0xfef0, 0xfef0}, // faa_ALEF_MAKSURA, // ى
        {0x0640, 0x0640, 0x0640, 0x0640, 0x0640}, // faa_TATWEEL, // ـ
        {0xfefb, 0xfefb, 0xfefb, 0xfefc, 0xfefc}, // faa_LAAM_ALEF, // لا
        {0xfef7, 0xfef7, 0xfef7, 0xfef8, 0xfef8}, // faa_LAAM_ALEF_HAMZA_ABOVE, // لأ
};
unsigned char FarsiType::GetFACharPlace(const std::string &fa_character, const std::string &prevFAChar, const std::string &nextFAChar)
{
    bool in_previous = false;
    bool in_next = false;
    for (auto const &fachar : fa_AlphabetsAllForms)
    {
        if (prevFAChar != "ISNOTFA" || fachar[faa_Unicode] == prevFAChar)
            in_previous = true;
        if (nextFAChar != "ISNOTFA" || fachar[faa_Unicode] == nextFAChar)
            in_next = true;
    }

    if (in_previous && in_next)
        return 3;
    if (in_next)
        return 2;
    if (in_previous)
        return 1;
    else
        return 0;
}

bool FarsiType::IsFACharBeginner(const std::string &fa_character)
{
    return fa_character == fa_AlphabetsAllForms[faa_ALEF_HAMZEH_ABOVE][faa_Unicode] ||
           fa_character == fa_AlphabetsAllForms[faa_ALEF_HAMZEH_ABOVE][faa_Unicode] ||
           fa_character == fa_AlphabetsAllForms[faa_ALEF_MAD_ABOVE][faa_Unicode] ||
           fa_character == fa_AlphabetsAllForms[faa_ALEF][faa_Unicode] ||
           fa_character == fa_AlphabetsAllForms[faa_HAMZEH][faa_Unicode] ||
           fa_character == fa_AlphabetsAllForms[faa_VAAV_HAMZEH_ABOVE][faa_Unicode] ||
           fa_character == fa_AlphabetsAllForms[faa_ALEF_HAMZEH_BELOW][faa_Unicode] ||
           fa_character == fa_AlphabetsAllForms[faa_DAAL][faa_Unicode] ||
           fa_character == fa_AlphabetsAllForms[faa_ZAAL][faa_Unicode] ||
           fa_character == fa_AlphabetsAllForms[faa_REH][faa_Unicode] ||
           fa_character == fa_AlphabetsAllForms[faa_ZEH][faa_Unicode] ||
           fa_character == fa_AlphabetsAllForms[faa_JEH][faa_Unicode] ||
           fa_character == fa_AlphabetsAllForms[faa_VAAV][faa_Unicode] ||
           fa_character == fa_AlphabetsAllForms[faa_ALEF_MAKSURA][faa_Unicode];
}

unsigned char FarsiType::FindFACharIndex(const std::string &fa_character)
{
    for (int i = 0; i < fa_AlphabetsAllForms.size(); ++i)
    {
        if (fa_character == fa_AlphabetsAllForms[i][faa_Unicode] ||
            fa_character == fa_AlphabetsAllForms[i][faa_Isolated] ||
            fa_character == fa_AlphabetsAllForms[i][faa_Beginner] ||
            fa_character == fa_AlphabetsAllForms[i][faa_Medium] ||
            fa_character == fa_AlphabetsAllForms[i][faa_Final])
            return i;
        else
            continue;
    }
    return fa_AlphabetsAllForms.size();
}
int FarsiType::FindFACharIndex(int codepoint)
{
    for (int i = 0; i < fa_AlphabetsAllFormsInt.size(); ++i)
    {
        if (codepoint == fa_AlphabetsAllFormsInt[i][faa_Unicode] ||
            codepoint == fa_AlphabetsAllFormsInt[i][faa_Isolated] ||
            codepoint == fa_AlphabetsAllFormsInt[i][faa_Beginner] ||
            codepoint == fa_AlphabetsAllFormsInt[i][faa_Medium] ||
            codepoint == fa_AlphabetsAllFormsInt[i][faa_Final])
            return i;
        else
            continue;
    }
    return fa_AlphabetsAllFormsInt.size();
}
bool FarsiType::IsFAChar(const std::string &fa_character)
{
    for (auto const &fachar : fa_AlphabetsAllForms)
    {
        if (fa_character == fachar[faa_Unicode] ||
            fa_character == fachar[faa_Isolated] ||
            fa_character == fachar[faa_Beginner] ||
            fa_character == fachar[faa_Medium] ||
            fa_character == fachar[faa_Final])
            return true;
        else
            continue;
    }
    return false;
}
bool FarsiType::IsFAChar(int codepoint)
{
    for (auto const &fachar : fa_AlphabetsAllFormsInt)
    {
        if (codepoint == fachar[faa_Unicode] ||
            codepoint == fachar[faa_Isolated] ||
            codepoint == fachar[faa_Beginner] ||
            codepoint == fachar[faa_Medium] ||
            codepoint == fachar[faa_Final])
            return true;
        else
            continue;
    }
    return false;
}
std::vector<std::string> FarsiType::ReverseFAText(const std::string &str)
{
    std::vector<std::string> reversedStr;

    for (int j = str.size() - 1; j > 0; j -= 2)
    {
        if ((str[j] & 0xFF) <= 0x7F)
        {
            std::string tempStr = std::string() + str[j];
            reversedStr.insert(reversedStr.end(), tempStr);
            j++;
            continue;
        }

        if ((str[j - 1] & 0xFF) <= 0x7F)
        {
            std::string tempStr = std::string() + str[j - 1];
            reversedStr.insert(reversedStr.end(), tempStr);
            j++;
            continue;
        }
        std::string tempStr = std::string() + str[j - 1] + str[j];
        reversedStr.insert(reversedStr.end(), tempStr);
    }
    return reversedStr;
}

std::string FarsiType::GetFACharGlyph(const std::string &fa_character, const std::string &prevFAChar, const std::string &nextFAChar)
{
    if (!IsFAChar(fa_character))
        return fa_character;

    unsigned char facharPlace;
    unsigned char facharIndex;
    facharPlace = GetFACharPlace(fa_character, prevFAChar, nextFAChar);
    facharIndex = FindFACharIndex(fa_character);

    if (facharPlace == 3)
    {
        if (IsFACharBeginner(prevFAChar))
        {
            if (fa_AlphabetsAllForms[facharIndex][faa_Beginner] == fa_AlphabetsAllForms[faa_YEH][faa_Beginner])
            {
                return fa_AlphabetsAllForms[faa_ARABIC_YEH][faa_Beginner];
            }
            return fa_AlphabetsAllForms[facharIndex][faa_Beginner];
        }
        else
        {
            if (fa_AlphabetsAllForms[facharIndex][faa_Medium] == fa_AlphabetsAllForms[faa_YEH][faa_Medium])
            {
                return fa_AlphabetsAllForms[faa_ARABIC_YEH][faa_Medium];
            }
            return fa_AlphabetsAllForms[facharIndex][faa_Medium];
        }
    }
    else if (facharPlace == 2)
    {
        if (fa_AlphabetsAllForms[facharIndex][faa_Beginner] == fa_AlphabetsAllForms[faa_YEH][faa_Beginner])
        {
            return fa_AlphabetsAllForms[faa_ARABIC_YEH][faa_Beginner];
        }
        return fa_AlphabetsAllForms[facharIndex][faa_Beginner];
    }
    else if (facharPlace == 1)
    {
        if (IsFACharBeginner(prevFAChar))
        {
            if (fa_AlphabetsAllForms[facharIndex][faa_Isolated] == fa_AlphabetsAllForms[faa_YEH][faa_Isolated])
            {
                return fa_AlphabetsAllForms[faa_ALEF_MAKSURA][faa_Isolated];
            }
            return fa_AlphabetsAllForms[facharIndex][faa_Isolated];
        }
        else
        {
            if (fa_AlphabetsAllForms[facharIndex][faa_Final] == fa_AlphabetsAllForms[faa_YEH][faa_Final])
            {
                return fa_AlphabetsAllForms[faa_ALEF_MAKSURA][faa_Final];
            }
            return fa_AlphabetsAllForms[facharIndex][faa_Final];
        }
    }
    else
    {
        if (fa_AlphabetsAllForms[facharIndex][faa_Isolated] == fa_AlphabetsAllForms[faa_YEH][faa_Isolated])
        {
            return fa_AlphabetsAllForms[faa_ALEF_MAKSURA][faa_Isolated];
        }
        return fa_AlphabetsAllForms[facharIndex][faa_Isolated];
    }
}

std::string FarsiType::ConvertToFAGlyphs(const std::string &text)
{
    std::vector<std::string> reversed_text = ReverseFAText(text);
    std::string convertedText;
    std::string previous_fachar, next_fachar;

    for (int i = 0; i < reversed_text.size(); ++i)
    {

        if (!IsFAChar(reversed_text[i]))
        {
            convertedText.append(reversed_text[i]);
            continue;
        }
        if ((i - 1) < 0)
            previous_fachar = "ISNOTFA";
        else
        {
            if (IsFAChar(reversed_text[i - 1]))
                previous_fachar = reversed_text[i - 1];
            else
                previous_fachar = "ISNOTFA";
        }

        if ((i + 1) <= (reversed_text.size() - 1))
        {
            if (IsFAChar(reversed_text[i + 1]))
                next_fachar = reversed_text[i + 1];
            else
                next_fachar = "ISNOTFA";
        }
        else
            next_fachar = "ISNOTFA";

        std::string fa_glyph = GetFACharGlyph(reversed_text[i], next_fachar, previous_fachar);
        convertedText.append(fa_glyph);
    }
    return convertedText;
}
void FarsiType::FACodeList(int *codepoints)
{
    codepoints[512] = {0};
    for (size_t i = 0; i < 95; i++)
    {
        codepoints[i] = i + 32;
    }
    for (size_t i = 0; i < 32; i++)
    {
        codepoints[i + 95] = i + 160;
    }
    codepoints[127] = 1548;
    codepoints[128] = 1563;
    codepoints[129] = 1567;
    for (size_t i = 0; i < 26; i++)
    {
        codepoints[130 + i] = i + 1569;
    }
    for (size_t i = 0; i < 22; i++)
    {
        codepoints[156 + i] = i + 1600;
    }
    codepoints[178] = 1623;
    codepoints[179] = 1626;
    for (size_t i = 0; i < 17; i++)
    {
        codepoints[180 + i] = i + 1632;
    }
    codepoints[197] = 1652;
    codepoints[198] = 1662;
    codepoints[199] = 1670;
    codepoints[200] = 1688;
    codepoints[201] = 1697;
    codepoints[202] = 1705;
    codepoints[203] = 1711;
    codepoints[204] = 1722;
    codepoints[205] = 1728;
    codepoints[206] = 1738;
    codepoints[207] = 1740;
    codepoints[208] = 1749;
    for (size_t i = 0; i < 10; i++)
    {
        codepoints[209 + i] = 1776 + i;
    }
    codepoints[220] = 8242;
    codepoints[221] = 8243;
    codepoints[222] = 8249;
    codepoints[223] = 8250;
    for (size_t i = 0; i < 4; i++)
    {
        codepoints[224 + i] = 64342 + i;
    }
    for (size_t i = 0; i < 4; i++)
    {
        codepoints[228 + i] = 64378 + i;
    }
    for (size_t i = 0; i < 2; i++)
    {
        codepoints[232 + i] = 64394 + i;
    }
    for (size_t i = 0; i < 8; i++)
    {
        codepoints[234 + i] = 64398 + i;
    }
    for (size_t i = 0; i < 2; i++)
    {
        codepoints[242 + i] = 64414 + i;
    }
    codepoints[244] = 64421;
    for (size_t i = 0; i < 2; i++)
    {
        codepoints[245 + i] = 64428 + i;
    }
    for (size_t i = 0; i < 2; i++)
    {
        codepoints[247 + i] = 64488 + i;
    }
    for (size_t i = 0; i < 4; i++)
    {
        codepoints[249 + i] = 64508 + i;
    }
    codepoints[243] = 65010;
    codepoints[245] = 65020;
    for (size_t i = 0; i < 141; i++)
    {
        codepoints[246 + i] = 65136 + i;
    }
    codepoints[387] = 65548;
    codepoints[38] = 64510;
    codepoints[389] = 64511;
    codepoints[390] = 64509;
}