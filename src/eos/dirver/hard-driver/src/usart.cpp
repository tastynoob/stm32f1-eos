#include "usart.hpp"
#include "gpio.hpp"
#include "stdio.h"
#include "math.h"

#include "rcc.hpp"

void CUSART::ClockOn() {
	switch ((int)this) {
		case USART1_BASE:
			rcc.APB2Cmd(_USART1, ENABLE);
			pa.ClockOn();
			pa.PinConfig(9, AF_PP, _50MHz);
			pa.PinConfig(10, IN_FLOATING, _in_);
			break;
		case USART2_BASE:
			rcc.APB1Cmd(_USART2, ENABLE);
			pa.ClockOn();
			pa.PinConfig(2, AF_PP, _50MHz);
			pa.PinConfig(3, IN_FLOATING, _in_);
			break;
		case USART3_BASE:
			rcc.APB1Cmd(_USART3, ENABLE);
			pa.ClockOn();
			pb.PinConfig(10, AF_PP, _50MHz);
			pb.PinConfig(11, IN_FLOATING, _in_);
			break;
	}

	{
		//一位停止位
		BitReset(CR2, 13);
		BitReset(CR2, 12);


		//8位数据，关闭校验使能
		BitReset(CR1, 12);
		BitReset(CR1, 10);
		BitReset(CR1, 9);
		BitSet(CR1, 2);
		BitSet(CR1, 3);


		BitReset(CR3, 9);
		BitReset(CR3, 8);

		uint32 apbclock;
		if ((int)this == USART1_BASE) {
			apbclock = 72 * 1000 * 1000;
		}
		else {
			apbclock = 36 * 1000 * 1000;
		}
		float uart_div = (float)(apbclock / (16 * (115200)));
		uint16 a = uart_div;
		uint16 b = (uart_div - a) * 16;
		a <<= 4;
		a += b;
		BRR = a;
	}

	BitSet(CR1, 13); //使能串口
	BitReset(SR, 6); //清除TC位
}

inline bool CUSART::Available() {
	return BitGet(SR, 5);
}

CUSART& CUSART::operator<<(const char* str) {
	int cnt = 0;
	for (int i = 0; str[i]; i++) {

		DR = (str[i] & 0x01ff); //发送数据
		while (BitGet(SR, 7) == 0) { //数据发送超时
			cnt++;
			if (cnt > 1e5)
				return *this;
		}
	}
	return *this;
}

CUSART& CUSART::operator<<(int a) {
	char str[20];
	sprintf(str, "%d", a);
	*this << str;
	return *this;
}

CUSART& CUSART::operator<<(float a) {
	char str[20];
	sprintf(str, "%.4g", a);
	*this << str;
	return *this;
}


CUSART& CUSART::operator<<(byte a) {
	DR = (a & 0x01ff); //发送数据
	int cnt = 0;
	while (BitGet(SR, 7) == 0) { //数据发送超时
		cnt++;
		if (cnt > 1e5)
			return *this;
	}
	return *this;
}






CUSART& CUSART::operator>>(char* buffer) {
	int len = 0;
	int i = 2000;
	while (BitGet(SR, 5) == 0) //阻塞，等待数据输入
		;
	while (i--) {
		if (BitGet(SR, 5) == 1) {
			buffer[len++] = (DR & 0x01ff);
			if (buffer[len - 1] == '\n')
				break;
			i = 2000;
		}
	}
	buffer[len] = 0;
	return *this;
}

