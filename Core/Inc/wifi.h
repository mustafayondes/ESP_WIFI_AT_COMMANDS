/*
 * wifi.h
 *
 *  Created on: Sep 4, 2023
 *      Author: MUSTAFA
 */

#ifndef INC_WIFI_H_
#define INC_WIFI_H_


void wifi_test();
void wifi_connect();
void ESP32_SendDataToThingSpeak( char * API_KEY,int  value);
#endif /* INC_WIFI_H_ */
