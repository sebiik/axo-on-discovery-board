uint8_t text[11*4];
uint8_t tY[128];

/* Scaled x2 text. Returns a page to be sent to the SSD1306 based on contents of text */
void calcTextPage(uint8_t page, uint8_t tPage[128]) {
  uint8_t col = 0;
  for(uint8_t nc = 0; nc < 11; nc++) {
    uint8_t ascii_32 = text[nc + 11 * (page/2)] - ' ';
    if(ascii_32 < 0 || ascii_32 >= 128-32) ascii_32 = 0;
    const uint8_t *adChar = tiar_font5x8 + ascii_32 * 5;
    for(uint8_t slice = 0; slice < 5; slice++) {
      uint8_t s;
      if((page & 1) == 0) {
        s = nibbleToByte[ adChar[slice]       & 15];  // low nibble
      }
      else {
        s = nibbleToByte[(adChar[slice] >> 4) & 15]; // high nibble
      }
      tPage[col] = s; col++;
      tPage[col] = s; col++;
    }
    tPage[col] = 0; col++; // separator space
  }
  while(col<128) {
    tPage[col] = 0; col++;
  } // space padding
}

void _calcScopePage(int page, uint8_t tPage[128]) {
  for(int i=0;i<128;i++) {
  	uint16_t y = ((attr_scope.t[i]+64)*3 )/8;
    tPage[i] = vBar(y,page);
  }
}

void calcScopePage(int page, uint8_t tPage[128]) {
  if(page<2) {
  	calcTextPage(page, tPage);
  }
  else{
    uint16_t y0 = tY[0];
    uint16_t y1 = tY[1];
    uint16_t y2;
    for(int i = 0; i < 128; i++) {
      if(i < 127) y2 = tY[i + 1];
      uint16_t yM, ym;
      yM = ym = y1;
      uint16_t y = (y0 + y1) >> 1;
      yM = y > yM ? y : yM;
      ym = y < ym ? y : ym;
      y = (y2 + y1) >> 1;
      yM = y > yM ? y : yM;
      ym = y < ym ? y : ym;
      if(ym == yM) if(yM > 0) ym--; else yM++;
      tPage[i] = vBar(yM, page) & ~vBar(ym, page);
      y0 = y1;
      y1 = y2;
    }
  }
}

void sendTextPage(int page) {
  cmd(COLUMNADDR, 0, 127);    // Column start end
  cmd(PAGEADDR, page, page);  // Page start end

  if(attr_type == 1106) {
    cmd(0xB0 + page);//set page address
    cmd(2 & 0xf);//set lower column address
    cmd(0x10 | (2 >> 4));//set higher column address
  }

  txbuf[0] = 0x40;
  if(mode == 0) {
    calcTextPage(page, txbuf+1);
    i2cMasterTransmitTimeout(&I2CD1, attr_I2CADDR, txbuf, 129, rxbuf, 0, 10);
  }
  else if(mode == 1) {
    if(page==1)
      for(int i=0;i<128;i++)
        tY[i]=((attr_scope.t[i]+64)*3 )>>3;
    calcScopePage(page, txbuf+1);
    i2cMasterTransmitTimeout(&I2CD1, attr_I2CADDR, txbuf, 129, rxbuf, 0, 10);
  }
}
