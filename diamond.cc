/* Copyright 2024 Nicholas Vinson
 *
 * SPDX-License-Identifier: MIT
 *
 * Licensed under the MIT License;
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * https://opensource.org/license/mit
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include<iostream>
#include<print>
#include<ranges>
#include<string>
#include<vector>

constexpr int MAX_WIDTH = 256;

int error(std::string_view app_name) {
    std::print(std::cerr, "Usage: {} N where 1 <= N <= {}\n", app_name, MAX_WIDTH);
    return 1;
}

int parse_n(unsigned int &n, std::string_view s) {
    int state = 0;
    n = 0;
    for (auto c : s) {
        switch(c) {
        case '+':
            if (state == 0) {
                state = 1;
            } else {
                return 1;
            }
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            if (state == 0 || state == 1) {
                state = 2;
            }
            if (state == 2) {
                n = n * 10 + c - '0';
                if (n > MAX_WIDTH) {
                    return 1;
                }
            } else {
                return 1;
            }
            break;
        default:
            return 1;
        }
    }
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return error(argv[0]);
    }

    unsigned int n;
    if (parse_n(n, argv[1])) {
        return error(argv[0]);
    }

    int buf_len = n + !(n & 1);

    std::vector<char> star_buf(buf_len, '*');
    std::vector<char> ws_buf(buf_len >> 1, ' ');

    for (auto i = buf_len - 1 - !(n & 1); i >= 0; i -= 2) {
        for (auto v : std::ranges::drop_view(ws_buf, (buf_len >> 1) - i / 2)) {
            std::cout << v;
        }
        for (auto v : std::ranges::drop_view(star_buf, i + !(n & 1))) {
            std::cout << v;
        }
        std::cout << '\n';
    }

    for (auto i = 2; i < buf_len; i += 2) {
        for (auto v : std::ranges::drop_view(ws_buf, (buf_len >> 1) + !(n & 1) - i / 2)) {
            std::cout << v;
        }
        for (auto v : std::ranges::drop_view(star_buf, i)) {
            std::cout << v;
        }
        std::cout << '\n';
    }
    return 0;
}
