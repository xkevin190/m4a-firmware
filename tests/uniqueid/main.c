/*
 * Copyright (c) 2022 Mesh4all <mesh4all.org>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @brief       storage file
 *
 * @author      xkevin190 <kevinvelasco193@gmail.com>
 */
#include <string.h>
#include <errno.h>

#include "embUnit.h"
#include "uniqueid.h"

void get_unique_since_mac(ipv6_addr_t *output) {
    ipv6_addr_t header = {
        .u8 = {0},
    };
    char addr_cpu[CPUID_LEN] = {0};
    CPUID(addr_cpu);
    ipv6_addr_from_str(&header, CONFIG_HEADER_ADDRESS_ID);
    memcpy((char *)output->u8, (char *)header.u8, 4);
    strncat((char *)output->u8, addr_cpu, 4);
}

void test_get_ipv6Address(void) {
    ipv6_addr_t ipv6 = {
        .u8 = {0},
    };
    subnet_to_ipv6(&ipv6);

#ifdef CONFIG_MODE_STATIC
    ipv6_addr_t output = {
        .u8 = {0},
    };
    ipv6_addr_print(&ipv6);
    get_unique_since_mac(&output);
    TEST_ASSERT_EQUAL_INT(1, ipv6_addr_equal(&ipv6, &output));
#endif
}

Test *tests_get_unique_id(void) {
    EMB_UNIT_TESTFIXTURES(fixtures){
        new_TestFixture(test_get_ipv6Address),
    };

    EMB_UNIT_TESTCALLER(tests_get_unique_id, NULL, NULL, fixtures);

    return (Test *)&tests_get_unique_id;
}

int main(void) {
    TESTS_START();
    TESTS_RUN(tests_get_unique_id());
    TESTS_END();
    return 0;
}
