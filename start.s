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

    .global _start

    .text
_start:
    mov (%rsp), %edi
    lea 8(%rsp), %rsi
    call main
    mov %eax, %edi
    call exit_group

    .section .note.GNU-stack,"",%progbits
