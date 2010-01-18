#include <fstream>
#include <iostream>
#include "card.h"
#include "resource.h"
#include "yaml-cpp/yaml.h"

namespace dminion {

void LoadCards() {
  LoadCard("cards/custom/test.yaml");
}

game::Card* LoadCard(const string& name) {
  std::string parsedName, description;
  std::ifstream fin("cards/custom/test.yaml");
  YAML::Parser parser(fin);
  YAML::Node doc;

  game::Card* card = new game::Card();

  while (parser.GetNextDocument(doc)) {
    doc["name"] >> parsedName;
    doc["description"] >> description;
  }

  card->name = parsedName;
  card->description = description;

  resource::AddCard(card);
  
  std::cout << "Card Loaded: " << card->name << std::endl;
  std::cout << "Description: " << card->description << std::endl;
}

namespace game {

const string& Card::GetName() const {
  return name;
}

const string& Card::GetDescription() const {
  return description;
}

} // namespace game

} // namespace dminion
