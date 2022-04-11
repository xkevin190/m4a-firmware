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
 * @{
 * @file        radio.h
 * @brief       this module content all functons of radio
 * @author      xkevin190 <kevinvelasco193@gmail.com.com>
 *
 */

#ifndef RADIO_H
#define RADIO_H

#include "net/gnrc.h"
#include "net/netdev.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief this function is used to send the sensors values
 *
 * @param[in] max_ifaces    Receives the number of ifaces founded
 * @note Precondition: use the gnrc_netif_numof() this functions allows you known how many
 * interfaces are connected and initialized
 */

uint8_t *get_ieee802154_iface(uint8_t max_ifaces);

int set_global_ipv6_to_radio(void);

#ifdef __cplusplus
}
#endif
#endif /* RADIO_H */
