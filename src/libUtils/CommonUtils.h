/*
 * Copyright (C) 2021 Zilliqa
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef ZILLIQA_SRC_LIBUTILS_COMMONUTILS_H_
#define ZILLIQA_SRC_LIBUTILS_COMMONUTILS_H_

namespace CommonUtils {
// Release STL container cache forcefully
void ReleaseSTLMemoryCache();

// Generate random number between two integers
uint64_t GenerateRandomNumber(const uint64_t& low, const uint64_t& high);
}  // namespace CommonUtils

#endif  // ZILLIQA_SRC_LIBUTILS_COMMONUTILS_H_
