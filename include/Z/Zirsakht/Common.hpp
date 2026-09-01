#pragma once

#if defined(_MSC_VER) && (_MSC_VER < 1900)
#define ZIRSAKHT_NOEXCEPT _NOEXCEPT
#define ZIRSAKHT_CONSTEXPR
#else
#define ZIRSAKHT_NOEXCEPT noexcept
#define ZIRSAKHT_CONSTEXPR constexpr
#endif
