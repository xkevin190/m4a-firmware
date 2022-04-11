
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
 * @brief  radio
 *
 * @author  xkevin190 <kevinvelasco193@gmail.com>
 */
#include <stdint.h>
#include <stdio.h>
#include "net/gnrc/netif.h"
#include "net/netif.h"
#include "net/netdev/ieee802154.h"
#include "net/gnrc.h"
#include "uniqueid.h"
#include "radio.h"

#define STATIC_IFACE (4)

uint8_t get_ieee802154_iface(uint8_t max_ifaces) {
    gnrc_netif_t *iface;
    if (max_ifaces > 0) {
        iface = gnrc_netif_get_by_type(NETDEV_AT86RF2XX, NETDEV_INDEX_ANY);
        if(iface != NULL){
            return iface->pid;
        }
        else{
            return 0;
        }
    }
    return 0;
}

int set_global_ipv6_to_radio(void) {
    ipv6_addr_t global_ipv6 = {
        .u8 = {0},
    };
    subnet_to_ipv6(&global_ipv6);

    gnrc_netif_t *iface = gnrc_netif_get_by_pid(STATIC_IFACE);
    if (iface == NULL) {
        printf("Error: interface doesn't exists.\n");
        return -1;
    }

    /* Add node IPv6 global address */
    if (gnrc_netif_ipv6_addr_add(iface, &global_ipv6, 64, GNRC_NETIF_IPV6_ADDRS_FLAGS_STATE_VALID) <
        0) {
        printf("Error: Couldn't add IPv6 global address\n");
        return -1;
    }

    return 0;
}