//
// Created by nbdy on 26.11.21.
//

#include "ModuleShop.h"

ModuleShop::ModuleShop() : IModule(ModuleInformation{"ModuleShop"}, {ModuleDependency {"ModuleManager"}}) {}

void ModuleShop::drawModuleTypeSelector(float &i_fX, float &i_fY) {
  const uint32_t btnWidth = 64;
  const uint32_t btnHeight = 32;

  i_fX += 2;
  if (GuiButton(Rectangle{i_fX, i_fY, btnWidth, btnHeight}, "Local")) {
#ifdef USE_OHLOG
    DLOG("Reloading locally available modules");
#endif
    if(m_pCMM != nullptr) {
      m_LocalModules = ModuleLoader::loadDirectory<IModule>(m_pCMM->getModulesDirectory(), true);
#ifdef USE_OHLOG
      DLOGA("Found %i local modules", m_LocalModules.size());
#endif
    } else {
#ifdef USE_OHLOG
      WLOG("The module manager dependency is not satisfied. This module will not work properly.");
#endif
    }

    m_sListString = ModuleManager::getModuleNamesDelimited(";", m_LocalModules);
  }
  i_fX += btnWidth;

  i_fX += 2;
  if (GuiButton(Rectangle{i_fX, i_fY, btnWidth, btnHeight}, "Shop")) {
    // TODO
  }
  i_fX += btnWidth;
}

void ModuleShop::drawModuleSearch(float &i_fX, float &i_fY) {
  const uint32_t editTextWidth = 200;
  const uint32_t editTextHeight = 32;
  const uint32_t btnHeight = 32;
  const uint32_t btnWidth = btnHeight;

  char *placeholder = "placeholder";
  i_fX += 2;
  GuiTextBox(Rectangle{i_fX, i_fY, editTextWidth, editTextHeight}, placeholder,
             12, true); // TODO: process input
  i_fX += editTextWidth;

  i_fX += 2;
  if (GuiButton(Rectangle{i_fX, i_fY, btnWidth, btnHeight}, GuiIconText(RICON_LENS, ""))) {
    // TODO
  }
  i_fX += btnWidth;
}

void ModuleShop::drawModuleCounts(float &i_fX, float &i_fY) {
  const uint32_t lblWidth = 64;
  const uint32_t lblHeight = 16;

  GuiLabel(Rectangle{i_fX, i_fY, lblWidth, lblHeight}, ("Module count:  " + std::to_string(m_LocalModules.size())).c_str());
}

void ModuleShop::drawSettingsButton(float &i_fX, float &i_fY) {
  const uint32_t btnWidth = 64;
  const uint32_t btnHeight = 32;

  i_fX = SCREEN_WIDTH - btnWidth - 2;
  if (GuiButton(Rectangle{i_fX, i_fY, btnWidth, btnHeight}, "Settings")) {
    // TODO
  }
}

void ModuleShop::drawModuleList(float &i_fX, float &i_fY) {
  const uint32_t listWidth = SCREEN_WIDTH / 5;
  const float listHeight = static_cast<float>(SCREEN_HEIGHT) - i_fY - 2;

  if(!m_sListString.empty()) {
    i_fX += 2;
    m_i32PrevListSelection = m_i32ListSelection;
    m_i32ListSelection = GuiListView(Rectangle{i_fX, i_fY, listWidth, listHeight}, m_sListString.c_str(), nullptr, m_i32ListSelection);
    i_fX += listWidth + 2;
  }
}

void ModuleShop::drawModuleView(float &i_fX, float &i_fY) {
  const float xOffset = i_fX;
  const float yOffset = i_fY;

  const uint32_t btnWidth = 64;
  const uint32_t btnHeight = 32;
  /*
  ModuleWrapper<IModule>* module = nullptr;
  if(m_pCMM->getModuleByIndex(m_i32ListSelection, module)) {
    i_fX += 2;
    i_fY += 2;
    module->getModule()->drawInformation(i_fX, i_fY);
    i_fX += 2;
    i_fY += 100;
    module->getModule()->drawDependencies(i_fX, i_fY, 128, SCREEN_HEIGHT - i_fY - 18);

    i_fX = xOffset + 160;
    i_fY = yOffset;
    if(GuiButton(Rectangle{i_fX, i_fY, btnWidth, btnHeight}, "Delete")) {
      // module.get
    }
  }
   */
}

void ModuleShop::draw(float i_fX, float i_fY) {
  /*
  if(m_pCMM == nullptr) {
    if(!getDependency("ModuleManager", m_pCMM)) {
      ELOG("Could not find ModuleManager dependency");
    }
  }
   */

  const float startX = i_fX;
  const uint32_t topRowHeight = 32;

  // Top Row
  i_fX += 2;
  i_fY += 2;
  drawModuleTypeSelector(i_fX, i_fY);
  drawModuleSearch(i_fX, i_fY);
  i_fX += 2;
  drawModuleCounts(i_fX, i_fY);
  drawSettingsButton(i_fX, i_fY);

  // ListView
  i_fY += topRowHeight + 2;
  i_fX = startX + 2;
  drawModuleList(i_fX, i_fY);

  // ModuleView
  if(m_i32ListSelection != -1) {
    drawModuleView(i_fX, i_fY);
  }
}

F_CREATE(ModuleShop)
