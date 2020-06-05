class Menu;
class MenuComponentRenderer;
class MenuSystem;


// *********************************************************
// MenuComponent
// *********************************************************
MenuComponent::MenuComponent(const char* name, SelectFnPtr select_fn)
: _name(name),
  _has_focus(false),
  _is_current(false),
  _select_fn(select_fn) { }


const char* MenuComponent::get_name() const {
  return _name;
}


void MenuComponent::set_name(const char* name) {
  _name = name;
}


bool_t MenuComponent::has_focus() const {
  return _has_focus;
}


bool_t MenuComponent::is_current() const {
  return _is_current;
}


void MenuComponent::set_current(bool_t is_current) {
  _is_current = is_current;
}


Menu* MenuComponent::select() {
  if (_select_fn != nullptr)
  _select_fn(this);

  return nullptr;
}


void MenuComponent::set_select_function(SelectFnPtr select_fn) {
  _select_fn = select_fn;
}


// *********************************************************
// Menu
// *********************************************************
Menu::Menu(const char* name, SelectFnPtr select_fn)
: MenuComponent(name, select_fn),
  _p_current_component(nullptr),
  _menu_components(nullptr),
  _p_parent(nullptr),
  _num_components(0),
  _current_component_num(0),
  _previous_component_num(0) { }


bool_t Menu::next(bool_t loop) {
  _previous_component_num = _current_component_num;

  if (!_num_components) {
    return false;
  }
  else if (_current_component_num != _num_components - 1) {
    _current_component_num++;
    _p_current_component = _menu_components[_current_component_num];

    _p_current_component->set_current();
    _menu_components[_previous_component_num]->set_current(false);

    return true;
  }
  else if (loop) {
    _current_component_num = 0;
    _p_current_component = _menu_components[_current_component_num];

    _p_current_component->set_current();
    _menu_components[_previous_component_num]->set_current(false);

    return true;
  }
  return false;
}


bool_t Menu::prev(bool_t loop) {
  _previous_component_num = _current_component_num;

  if (!_num_components) {
    return false;
  }
  else if (_current_component_num != 0) {
    _current_component_num--;
    _p_current_component = _menu_components[_current_component_num];

    _p_current_component->set_current();
    _menu_components[_previous_component_num]->set_current(false);

    return true;
  }
  else if (loop) {
    _current_component_num = _num_components - 1;
    _p_current_component = _menu_components[_current_component_num];

    _p_current_component->set_current();
    _menu_components[_previous_component_num]->set_current(false);

    return true;
  }
  return false;
}


Menu* Menu::activate() {
  if (!_num_components)
  return nullptr;

  MenuComponent* pComponent = _menu_components[_current_component_num];

  if (pComponent == nullptr)
  return nullptr;

  return pComponent->select();
}


Menu* Menu::select() {
  MenuComponent::select();
  return this;
}


void Menu::reset() {
  for (int i = 0; i < _num_components; ++i)
  _menu_components[i]->reset();

  _p_current_component->set_current(false);
  _previous_component_num = 0;
  _current_component_num = 0;
  _p_current_component = _num_components ? _menu_components[0] : nullptr;
  _p_current_component->set_current();
}


void Menu::add_item(MenuItem* p_item) {
  add_component((MenuComponent*) p_item);
}


void Menu::add_menu(Menu* p_menu) {
  add_component((MenuComponent*) p_menu);
  p_menu->set_parent(this);
}


void Menu::add_component(MenuComponent* p_component) {
  // Resize menu component list, keeping existing items.
  // If it fails, there the item is not added and the function returns.
  _menu_components = (MenuComponent**) realloc(_menu_components,
                                              (_num_components + 1)
                                              * sizeof(MenuComponent*));
  if (_menu_components == nullptr)
  return;

  _menu_components[_num_components] = p_component;

  if (_num_components == 0) {
    _p_current_component = p_component;
    _p_current_component->set_current();
  }

  _num_components++;
}


Menu const* Menu::get_parent() const {
  return _p_parent;
}


void Menu::set_parent(Menu* p_parent) {
  _p_parent = p_parent;
}


MenuComponent const* Menu::get_menu_component(uint8_t index) const {
  return _menu_components[index];
}


MenuComponent const* Menu::get_current_component() const {
  return _p_current_component;
}


uint8_t Menu::get_num_components() const {
  return _num_components;
}


uint8_t Menu::get_current_component_num() const {
  return _current_component_num;
}


uint8_t Menu::get_previous_component_num() const {
  return _previous_component_num;
}


void Menu::render(MenuComponentRenderer const& renderer) const {
  renderer.render_menu(*this);
}


// *********************************************************
// BackMenuItem
// *********************************************************
BackMenuItem::BackMenuItem(const char* name, SelectFnPtr select_fn, MenuSystem* ms)
: MenuItem(name, select_fn),
  _menu_system(ms) { }


Menu* BackMenuItem::select() {
  if (_select_fn!=nullptr)
  _select_fn(this);

  if (_menu_system!=nullptr)
  _menu_system->back();

  return nullptr;
}


void BackMenuItem::render(MenuComponentRenderer const& renderer) const {
  renderer.render_back_menu_item(*this);
}


// *********************************************************
// MenuItem
// *********************************************************
MenuItem::MenuItem(const char* name, SelectFnPtr select_fn)
: MenuComponent(name, select_fn) { }


Menu* MenuItem::select() {
  MenuComponent::select();
  return nullptr;
}


void MenuItem::reset() {
  // Do nothing.
}


void MenuItem::render(MenuComponentRenderer const& renderer) const {
  renderer.render_menu_item(*this);
}


bool_t MenuItem::next(bool_t loop) {
  return false;
}


bool_t MenuItem::prev(bool_t loop) {
  return false;
}


// *********************************************************
// NumericMenuItem
// *********************************************************
NumericMenuItem::NumericMenuItem(const char* basename, SelectFnPtr select_fn,
  float value, float min_value, float max_value,
  float increment,
  FormatValueFnPtr format_value_fn)
: MenuItem(basename, select_fn),
  _value(value),
  _min_value(min_value),
  _max_value(max_value),
  _increment(increment),
  _format_value_fn(format_value_fn) {
    if (_increment < 0.0) _increment = -_increment;
    if (_min_value > _max_value) {
      float tmp = _max_value;
      _max_value = _min_value;
      _min_value = tmp;
    }
  };


void NumericMenuItem::set_number_formatter(FormatValueFnPtr format_value_fn) {
  _format_value_fn = format_value_fn;
}


Menu* NumericMenuItem::select() {
  _has_focus = !_has_focus;

  // Only run _select_fn when the user is done editing the value
  if (!_has_focus && _select_fn != nullptr)
  _select_fn(this);
  return nullptr;
}


void NumericMenuItem::render(MenuComponentRenderer const& renderer) const {
  renderer.render_numeric_menu_item(*this);
}


float NumericMenuItem::get_value() const {
  return _value;
}


float NumericMenuItem::get_min_value() const {
  return _min_value;
}


float NumericMenuItem::get_max_value() const {
  return _max_value;
}


String NumericMenuItem::get_formatted_value() const {
  String buffer;
  if (_format_value_fn != nullptr)
    buffer += _format_value_fn(_value);
  else
    buffer += _value;
  return buffer;
}


void NumericMenuItem::set_value(float value) {
  _value = value;
}


void NumericMenuItem::set_min_value(float value) {
  _min_value = value;
}


void NumericMenuItem::set_max_value(float value) {
  _max_value = value;
}


bool_t NumericMenuItem::next(bool_t loop) {
  _value += _increment;
  if (_value > _max_value) {
    if (loop)
    _value = _min_value;
    else
    _value = _max_value;
  }
  return true;
}


bool_t NumericMenuItem::prev(bool_t loop) {
  _value -= _increment;
  if (_value < _min_value) {
    if (loop)
    _value = _max_value;
    else
    _value = _min_value;
  }
  return true;
}


// *********************************************************
// MenuSystem
// *********************************************************
MenuSystem::MenuSystem(MenuComponentRenderer const& renderer)
: _p_root_menu(new Menu("", nullptr)),
  _p_curr_menu(_p_root_menu),
  _renderer(renderer) { }


bool_t MenuSystem::next(bool_t loop) {
  if (_p_curr_menu->_p_current_component->has_focus())
  return _p_curr_menu->_p_current_component->next(loop);
  else
  return _p_curr_menu->next(loop);
}


bool_t MenuSystem::prev(bool_t loop) {
  if (_p_curr_menu->_p_current_component->has_focus())
  return _p_curr_menu->_p_current_component->prev(loop);
  else
  return _p_curr_menu->prev(loop);
}


void MenuSystem::reset() {
  _p_curr_menu = _p_root_menu;
  _p_root_menu->reset();
}


void MenuSystem::select(bool_t reset) {
  Menu* pMenu = _p_curr_menu->activate();

  if (pMenu != nullptr)
  _p_curr_menu = pMenu;
  else
  if (reset)
  this->reset();
}


bool_t MenuSystem::back() {
  if (_p_curr_menu != _p_root_menu) {
    _p_curr_menu = const_cast<Menu*>(_p_curr_menu->get_parent());
    return true;
  }

  // We are already in the root menu
  return false;
}


Menu& MenuSystem::get_root_menu() const {
  return *_p_root_menu;
}


Menu const* MenuSystem::get_current_menu() const {
  return _p_curr_menu;
}


void MenuSystem::display() const {
  if (_p_curr_menu != nullptr)
  _renderer.render(*_p_curr_menu);
}


























enum SSD1306 {
  LCDWIDTH            = 128,
  LCDHEIGHT           = 64,
  SETCONTRAST         = 0x81, // 2byte cmd,256 contrast steps, reset = 7F
  DISPLAYON           = 0xAF, // entire display on
  DISPLAYOFF          = 0xAE, // entire display off
  DISPLAYALLON_RESUME = 0xA4,
  NORMALDISPLAY       = 0xA6, // invert = 0xA7
  DEACTIVATE_SCROLL   = 0x2E, // stop control scroll conf by 26 27 29 2A
  MEMORYMODE          = 0x20, // 2byte cmd, 0 horizontal, 1 vertical, 2 page addressing, 3 invalid
  COLUMNADDR          = 0x21, // 3bytes, start, end (included) valid in horizontal or vertical mode
  PAGEADDR            = 0x22, // 3bytes, start, end (included) valid in horizontal or vertical mode
  SETSTARTLINE_0      = 0x40, // set display RAM start line at 0
  SEGREMAP            = 0xA0, // segment remap 0 mapped to SEG0
  SETMULTIPLEX        = 0xA8, // 2 byte cmd, set mux ratio
  COMSCANDEC          = 0xC8, // scan from COM[N-1] to COM[0] (0xC0 is COM0 to COM[N-1])
  SETDISPLAYOFFSET    = 0xD3, // 2 byte cmd, vertical shift
  SETCOMPINS          = 0xDA, // 2 byte cmd, seq com pin conf, left right remap
  SETDISPLAYCLOCKDIV  = 0xD5, // 2 byte cmd, low nibble A[3:0]+1 = div ratio, high nibble A[7:4] freq, reset 1000b
  SETPRECHARGE        = 0xD9, // 2 byte cmd, precharge period A[3:0] phase1 A[7:4] phase2, reset:2
  SETVCOMDETECT       = 0xDB, // 2 byte Vcomh deselect level A[6:4] 000b 0.65xVcc 010b 0.77(reset) 011b 0.83
  CHARGEPUMP          = 0x8D, // Enable charge pump seq: 0x8D, 0x14, 0xAF (Charge pump setting, enable charge pump, display on)
  EXTERNALVCC         = 0x1,
  SWITCHCAPVCC        = 0x2
};

uint8_t const nibbleToByte[16]={
  0b00000000,
  0b00000011,
  0b00001100,
  0b00001111,
  0b00110000,
  0b00110011,
  0b00111100,
  0b00111111,
  0b11000000,
  0b11000011,
  0b11001100,
  0b11001111,
  0b11110000,
  0b11110011,
  0b11111100,
  0b11111111
};

uint8_t const tBar[9]={
  //LSB up
  0b00000000,
  0b10000000,
  0b11000000,
  0b11100000,
  0b11110000,
  0b11111000,
  0b11111100,
  0b11111110,
  0b11111111
};

uint8_t *txbuf;

int32_t mode;
uint8_t invertLine = 0;

uint8_t text[11*4];    // text inputs
uint8_t textBuf[11*4]; // text inputs copy (to avoid flicker)
uint8_t tY[128];       // scope input copied and rescaled
bool disable;


/* Send command */
void cmd(uint8_t c) {
  txbuf[0] = 0;
  txbuf[1] = c;
  i2cMasterTransmitTimeout(&attr_I2CDRIVER, attr_I2CADDR, txbuf, 2, NULL, 0, 30);
}
void cmd(uint8_t c1, uint8_t c2) { cmd(c1); cmd(c2); }
void cmd(uint8_t c1, uint8_t c2, uint8_t c3) { cmd(c1, c2); cmd(c3); }


void drawPixel(uint8_t x, uint8_t y, uint8_t color) {
  if ((x >= LCDWIDTH) || (y >= LCDHEIGHT)) return;

  if (color == 1) // set pixel
    screenbuf[x + (y>>3) * LCDWIDTH ] |=  (1 << (y & 7));
  else if (color <= 0) // clear pixel
    screenbuf[x + (y>>3) * LCDWIDTH ] &= ~(1 << (y & 7));
  else // >= 2 inverts pixel
    screenbuf[x + (y>>3) * LCDWIDTH ] ^=  (1 << (y & 7));
}


void sendBuffer() {
  for (int page=0; page<8; ++page) { sendPage(page); }
}


void clearBuffer() {
	for (int i = 0; i < 128*8; ++i) { screenbuf[i] = 0; }
}


void fill(uint8_t v) {
  // Fill page with bit pattern
  cmd(COLUMNADDR, 0, 127); // Column start end
  cmd(PAGEADDR,   0,   7); // Page start end
  txbuf[0] = 0x40;
  for (int i = 1; i < 129; i++)
    txbuf[i] = v;
  for (int p = 0; p < 8; p++)
    i2cMasterTransmitTimeout(&attr_I2CDRIVER, attr_I2CADDR, txbuf, 129, NULL, 0, 30);
}


int drawTxt(int i, int NBC, uint8_t *tb, int page, uint8_t *tPage) {
  // Returns i
  for(int nc = 0; nc < NBC; nc++) {
    int ascii_32 = tb[nc] - ' ';
    const uint8_t *adChar = attr_fontObject.font5x8 + ascii_32 * 5;
    for(int slice = 0; slice < 5; slice++) { //slices are two pixel wide
      uint8_t s;
      if((page & 1) == 0)
        s = nibbleToByte[ adChar[slice]       & 15];  // low nibble
      else
        s = nibbleToByte[(adChar[slice] >> 4) & 15]; // high nibble
      tPage[i] = s; i++; // two pixel wide
      tPage[i] = s; i++;
    }
    tPage[i] = 0; i++; // separator space 1 pixel wide => 11 pixels per char
  }
  return i;
}


void calcTextPage(int page, uint8_t tPage[128]) {
  // Returns a page to be sent to the SSD1306 based on contents of text
  int i = 0;
  int tLine = page/2;
  uint8_t *tb = textBuf + 11*tLine;
  if(tb[0] >= ' ') // full text line
    i = drawTxt(i, 11, tb, page, tPage);
  else if(tb[0] == 1 ) { //strbar
    uint8_t filledBar = ((page & 1) == 0) ? 0b11100000 : 0b00111111;
    i = drawTxt(i, 5, tb + 2, page, tPage);
    while(i < 63) {tPage[i] = 0; i++;} // space padding
    if(tb[1] < 128) { //positive value => filled bar
      tPage[i] = 0; i++;
      for(i = 64; i < 63 + tb[1] && i < 128; i++) {
        tPage[i] = filledBar;
      }
    }
    else {  //negative value => hollow bar
      tPage[i] = filledBar; i++;
      uint8_t hollowBar = ((page & 1) == 0) ? 0b00100000 : 0b00100000;
      for(i = 64; i < 63 + 256 - tb[1] && i < 127; i++) {
        tPage[i] = hollowBar;
      }
      tPage[i] = filledBar;
      i++;
    }
  }
  else if(tb[0] == 2 ) { //bar
    uint8_t filledBar = ((page & 1) == 0) ? 0b11100000 : 0b00111111;
    if(tb[1] <= 128) { //positive value => filled bar
      tPage[i] = 0; i++;
      for(i = 0; i < tb[1]; i++) {
        tPage[i] = filledBar;
      }
    }
    else {  //negative value => hollow bar
      tPage[i] = filledBar; i++;
      uint8_t hollowBar = ((page & 1) == 0) ? 0b00100000 : 0b00100000;
      for(; i < 256 - tb[1]; i++) {
        tPage[i] = hollowBar;
      }
      tPage[i] = filledBar;
      i++;
    }
  }
  else if(tb[0] == 3 ) { //strbar2
    uint8_t filledBar = ((page & 1) == 0) ? 0b11110000 : 0b01111000;
    i = drawTxt(i, 5, tb + 3, page, tPage);
    for(;i < 63; i++) {tPage[i] = 0; } // space padding
    int v = tb[1 + (page & 1)];
    if(v < 128) { //positive value => filled bar
      tPage[i] = 0; i++;
      for(i = 64; i < 63 + v && i < 128; i++) {
        tPage[i] = filledBar;
      }
    }
    else {  //negative value => hollow bar
      tPage[i] = filledBar; i++;
      uint8_t hollowBar = ((page & 1) == 0) ? 0b10010000 : 0b01001000;
      for(i = 64; i < 63 + 256 - v && i < 127; i++) {
        tPage[i] = hollowBar;
      }
      tPage[i] = filledBar;
      i++;
    }
  }
  else if(tb[0] == 4 ) { //bar dble
    uint8_t filledBar = ((page & 1) == 0) ? 0b11110000 : 0b01111000;
    int v = tb[1 + (page & 1)];
    if(v <= 128) { //positive value => filled bar
      for(i = 0; i < v; i++) {
        tPage[i] = filledBar;
      }
    }
    else {  //negative value => hollow bar
      tPage[i] = filledBar; i++;
      uint8_t hollowBar = ((page & 1) == 0) ? 0b10010000 : 0b01001000;
      for(; i < 256 - v; i++) {
        tPage[i] = hollowBar;
      }
      tPage[i] = filledBar;
      i++;
    }
  }
  for(; i < 128; i++) {tPage[i] = 0;} // space padding

}


uint8_t vBar(uint8_t val, int page) {
  uint8_t _page =  7 - (val / 8);
  if(page > _page) return 0b11111111;  // below => light
  else if(page < _page) return 0;      // above => dark
  else return tBar[val & 7];
}


// on the Oled display, a "page" is a 128x8 stripe of pixels
// described by 128 bytes. The 128x64 OLED consists of 8 "pages"
// I calculate and transmit one page at a time.
// It saves memory as small buffers are enough to transmit them.
void calcScopePage(int page, uint8_t tPage[128]) {
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


void sendPage(int page) {
  //prepare transmission to the "page"
  cmd(COLUMNADDR, 0, 127);   // Column start end
  cmd(PAGEADDR, page, page);  // Page start end
  if(attr_type == 1106) {
    cmd(0xB0 + page);//set page address
    cmd(2 & 0xf);//set lower column address
    cmd(0x10 | (2 >> 4));//set higher column address
  }

  if(mode == 0) { // 4 text lines
    //on the beginning of drawing (page 0) we update the buffers
    if(page == 0)
      memcpy(textBuf, text, 11*4);
    calcTextPage(page, txbuf+1);
  }
  else if(mode == 1) { //Title and scope
    //on the beginning of drawing (page 0) we update the buffers
    if(page == 0) {
      //update the textBuffer
      memcpy(textBuf, text, 11*4);
      //update scope buffer
      memcpy(tY, attr_scope.t, 128);
      //scale for the display
      int8_t* stY = (int8_t*)tY;
      for(int i = 0; i < 128; i++) {
	      tY[i] = ((stY[i] + 64) * 3 ) >> 3;
      }
    }
    if(page < 2)
  	  calcTextPage(page, txbuf + 1);
    else
      calcScopePage(page, txbuf + 1);
  }
  else if(mode == 2) { //full screen scope
    //on the beginning of drawing (page 0) we update the buffers
    if(page == 0) {
      //update scope buffer
      memcpy(tY, attr_scope.t, 128);
      //scale for the display
      int8_t* stY = (int8_t*)tY;
      for(int i = 0; i < 128; i++) {
	      tY[i] = (stY[i] + 64) >> 1;
      }
    }
    calcScopePage(page, txbuf+1);
  }

  //transmit the page
  txbuf[0] = 0x40;

  // invert the highlighted line
  if (invertLine > 0) {
    if (page/2 + 1 == invertLine) {
      for(int i = 1; i<129; i++)
        txbuf[i] = ~txbuf[i];
    }
  }
  i2cMasterTransmitTimeout(&attr_I2CDRIVER, attr_I2CADDR, txbuf, 129, NULL, 0, 30);
}


void hw_init() {
  // Init sequence
  if(attr_type == 1106 || attr_type == 1306) {
    cmd(DISPLAYOFF);
    // 2 byte cmd,
    //  low nibble A[3:0]+1 = div ratio,
    //  high nibble A[7:4] freq  reset 1000b
    cmd(SETDISPLAYCLOCKDIV, 0x80);
    cmd(SETMULTIPLEX, LCDHEIGHT - 1);
    cmd(SETDISPLAYOFFSET, attr_type == 1306 ? 0x00 : 0x01);
    cmd(SETSTARTLINE_0);
    cmd(CHARGEPUMP, 0x14);
    cmd(MEMORYMODE, 0x00); //horizontal
    cmd(SEGREMAP | 0x1);
    cmd(COMSCANDEC);
    cmd(SETCOMPINS, 0x12);
    cmd(SETCONTRAST, attr_dimBacklight);
    cmd(SETPRECHARGE, 0xF1);
    cmd(SETVCOMDETECT, 0x40);
    cmd(DISPLAYALLON_RESUME);
    cmd(NORMALDISPLAY);
    cmd(DEACTIVATE_SCROLL);
    cmd(DISPLAYON);
  }
  else {
    cmd(DISPLAYOFF);
    cmd(SETDISPLAYCLOCKDIV, 0x0a0);// vs 80
    cmd(SETMULTIPLEX, 0x03f);	 //vs not in comment
    cmd(SETSTARTLINE_0);		       //idem
    cmd(MEMORYMODE, 0x00);        //02 vs00		/* page addressing mode vs line addressing mode*/
    cmd(SEGREMAP | 0x1);           //idem
    cmd(COMSCANDEC);               //idem
    // Flipmode
    // U8X8_C(0x0a0),				/* segment remap a0/a1*/
    // U8X8_C(0x0c0),				/* c0: scan dir normal, c8: reverse */
    cmd(SETCOMPINS, 0x012);   //idem		/* com pin HW config, sequential com pin config (bit 4), disable left/right remap (bit 5) */
    cmd(SETCONTRAST, 0x06f);    //vs 0xCF 		/* [2] set contrast control */
    cmd(SETPRECHARGE, 0x0d3);   //vs 0xF1 		/* [2] pre-charge period 0x022/f1*/
    cmd(SETVCOMDETECT, 0x020);  //vs 0x40 		/* vcomh deselect level */
    // if vcomh is 0, then this will give the biggest range for contrast control issue #98
    // restored the old values for the noname constructor, because vcomh=0 will not work for all OLEDs, #116
    cmd(DEACTIVATE_SCROLL);      //idem				/* Deactivate scroll */
    cmd(DISPLAYALLON_RESUME);    //idem				/* output ram to display */
    cmd(NORMALDISPLAY);          //idem				/* none inverted normal display mode */
    cmd(DISPLAYON);
  }
}


void setup() {
  static uint8_t _txbuf[132] __attribute__ ((section (".sram2")));
  txbuf = _txbuf;
  hw_init();
}

// THREADS
msg_t ThreadX2() {
  setup();
  while (!chThdShouldTerminate()) {
    if(!disable) {
      for(int i = 0; i < 8; i++) sendPage(i);
    }
    chThdSleepMilliseconds(32);
  }
  chThdExit((msg_t)0);
}

static msg_t ThreadX(void *arg) {
  ((attr_parent *)arg)->ThreadX2();
}


WORKING_AREA(waThreadX, 192); Thread *Thd;
