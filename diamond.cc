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

constexpr int STDIN_FILENO = 0;
constexpr int STDOUT_FILENO = 1;
constexpr int STDERR_FILENO = 2;

#define MAX_WIDTH_ 256
#define STRINGIFY(x) XSTRINGIFY(x)
#define XSTRINGIFY(x) #x

#ifdef __LP64__
typedef long ssize_t;
typedef unsigned long size_t;
typedef long intptr_t;
typedef unsigned long uintptr_t;
#else
# error "Only LP64 supported"
#endif

constexpr size_t MAX_WIDTH = MAX_WIDTH_;
constexpr const char MAX_WIDTH_STR[] = STRINGIFY(MAX_WIDTH_);

extern "C" {
    int main(int, char **);
    [[ noreturn ]] void exit_group(int);
    [[ noreturn ]] void _start();
    ssize_t write(int, const char *, size_t);
    void *memset(void *, int, size_t);
    void __stack_chk_fail(void);
}

void __stack_chk_fail(void) {
    exit_group(255);
}

void *memset(void *s, int c, size_t n) {
    for (int i = 0; i < n; i++) {
        ((char *)s)[i] = c;
    }
    return s;
}

size_t strlen(const char *s) {
    const char *t = s;
    while (*t++) ;
    return t - s;
}

int error(const char *app_name) {
    constexpr char usage[] = "Usage: ";
    constexpr char exp_text_prefix[] = " N where 1 <= N <= ";

    write(STDOUT_FILENO, usage, sizeof(usage) - 1);
    write(STDOUT_FILENO, app_name, strlen(app_name));
    write(STDOUT_FILENO, exp_text_prefix, sizeof(exp_text_prefix) - 1);
    write(STDOUT_FILENO, MAX_WIDTH_STR, sizeof(MAX_WIDTH_STR) - 1);
    write(STDOUT_FILENO, "\n", 1);

    return 1;
}

int parse_n(unsigned int &n, const char *s) {
    int state = 0;
    n = 0;
    while (char c = *s++) {
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

    int buf_len = n + (n & 1);

    char star_buf[MAX_WIDTH];
    char ws_buf[MAX_WIDTH];

    for (int i = 0; i < buf_len - 1; i++) {
        star_buf[i] = '*';
    }
    star_buf[buf_len - 1] = '\n';

    for (int i = 0; i < buf_len - 1; i++) {
        ws_buf[i] = ' ';
    }

    for (int i = buf_len - 2; i >= 0; i -= 2) {
        write(STDOUT_FILENO, ws_buf , i / 2);
        write(STDOUT_FILENO, star_buf + i, buf_len - i);
    }

    for (int i = (n & 1) << 1; i <= buf_len; i += 2) {
        write(STDOUT_FILENO, ws_buf , i / 2);
        write(STDOUT_FILENO, star_buf + i, buf_len - i);
    }
    return 0;
}
