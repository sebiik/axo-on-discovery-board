#include <MenuSystem.h>


// renderer
class MyRenderer : public MenuComponentRenderer {
public:
  void render(Menu const& menu) const {
    Serial.println("");
    for (int i = 0; i < menu.get_num_components(); ++i) {
      MenuComponent const* cp_m_comp = menu.get_menu_component(i);
      cp_m_comp->render(*this);

      if (cp_m_comp->is_current())
      Serial.print("<<< ");
      Serial.println("");
    }
  }

  void render_menu_item(MenuItem const& menu_item) const {
    Serial.print(menu_item.get_name());
  }

  void render_back_menu_item(BackMenuItem const& menu_item) const {
    Serial.print(menu_item.get_name());
  }

  void render_numeric_menu_item(NumericMenuItem const& menu_item) const {
    Serial.print(menu_item.get_name());
  }

  void render_menu(Menu const& menu) const {
    Serial.print(menu.get_name());
  }
};
MyRenderer my_renderer;


// forward declarations
void on_item1_selected(MenuComponent* p_menu_component);
void on_item2_selected(MenuComponent* p_menu_component);
void on_item3_selected(MenuComponent* p_menu_component);
void on_item4_selected(MenuComponent* p_menu_component);


// Menu variables
MenuSystem ms(my_renderer);

MenuItem mm_mi1("Level 1 - Item 1 (Item)", &on_item1_selected);
MenuItem mm_mi2("Level 1 - Item 2 (Item)", &on_item2_selected);
Menu         mu1("Level 1 - Item 3 (Menu)");
MenuItem mu1_mi1("Level 2 - Item 1 (Item)", &on_item3_selected);
MenuItem mu1_mi2("Level 2 - Item 2 (Item)", &on_item4_selected);


// Menu callback function
bool_t done = false;

void on_item1_selected(MenuComponent* p_menu_component) {
  Serial.println("Item1 Selected");
}

void on_item2_selected(MenuComponent* p_menu_component) {
  Serial.println("Item2 Selected");
}

void on_item3_selected(MenuComponent* p_menu_component) {
  Serial.println("Item3 Selected");
}

void on_item4_selected(MenuComponent* p_menu_component) {
  Serial.println("Item4 Selected");
  done = true;
}


// Standard arduino functions
void setup() {
  Serial.begin(9600);

  ms.get_root_menu().add_item(&mm_mi1);
  ms.get_root_menu().add_item(&mm_mi2);
  ms.get_root_menu().add_menu(&mu1);
  mu1.add_item(&mu1_mi1);
  mu1.add_item(&mu1_mi2);
}

void loop() {
  ms.display();

  // Simulate using the menu by walking over the entire structure.
  ms.select();
  ms.next();

  if (done) {
    ms.reset();
    done = false;
  }

  delay(2000);
}
