#include "char_fifo.h"

void char_fifo_init(struct char_fifo *cf, char *buff, uint8_t buff_size) {
	cf->buff = buff;
	cf->buff_size = buff_size;
	cf->pop_ndx = 0;
	cf->push_ndx = 0;
}

uint8_t char_fifo_is_empty(struct char_fifo *cf) {
	return cf->pop_ndx == cf->push_ndx;
}

uint8_t char_fifo_is_full(struct char_fifo *cf) {
	if(cf->push_ndx == 0)
		return cf->pop_ndx == (cf->buff_size - 1);
	return cf->push_ndx == (cf->pop_ndx - 1);
}

uint8_t char_fifo_inc_ndx(struct char_fifo *cf, uint8_t ndx) {
	if(ndx == cf->buff_size) return 0;
	else return ++ndx;
}

uint8_t char_fifo_push(struct char_fifo *cf, char ch) {
	if(char_fifo_is_full(cf))
		return 1;
	cf->buff[cf->push_ndx] = ch;
	cf->push_ndx = char_fifo_inc_ndx(cf, cf->push_ndx);
	return 0;
}

uint8_t char_fifo_pop(struct char_fifo *cf, char *ch) {
	if(char_fifo_is_empty(cf))
		return 1;
	*ch = cf->buff[cf->pop_ndx];
	cf->pop_ndx = char_fifo_inc_ndx(cf, cf->pop_ndx);
	return 0;
}

