#include <locale>

static std::wstring_convert<
    std::codecvt_utf8_utf16<wchar_t, 0x10ffff, std::little_endian>>
    converter;

/**
* @brief Windows helper function for converting narrow strings to wide
*
* @returns A wide string, constructed from a narrow string
*/
std::wstring stringToWstring(const std::string& src);

/**
* @brief Windows helper function for converting wide strings to narrow
*
* @returns A narrow string, constructed from a wide string
*/
std::string wstringToString(const wchar_t* src);

/**
* @brief Windows WMI Helper function to print the type associated with results
*
* @returns A string created from a BSTR
*/
std::string bstrToString(const BSTR src);




/////////////////////////////////////////////////////////////////////////////////
std::wstring stringToWstring(const std::string& src) {
  std::wstring utf16le_str;
  try {
    utf16le_str = converter.from_bytes(src);
  } catch (std::exception /* e */) {
    LOG(WARNING) << "Failed to convert string to wstring " << src;
  }

  return utf16le_str;
}

std::string wstringToString(const wchar_t* src) {
  if (src == nullptr) {
    return std::string("");
  }

  std::string utf8_str = converter.to_bytes(src);
  return utf8_str;
}

std::string bstrToString(const BSTR src) {
  return wstringToString(static_cast<const wchar_t*>(src));
}