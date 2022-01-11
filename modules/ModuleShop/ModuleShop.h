//
// Created by nbdy on 26.11.21.
//

#ifndef CARPI_MODULES_MODULESHOP_MODULESHOP_H_
#define CARPI_MODULES_MODULESHOP_MODULESHOP_H_


#define ENABLE_DRAW_FUNCTION
#include "modulepp.h"

#include "carpi_config.h"
#include "CMM.h"

/*
 * TODO(nbdy): ModuleShop
 *  - Load modules from server via json request
 *    - ModuleInformation
 *    - ModuleDependencies
 *  - Show as ListView
 *    - If entry is selected show Module Information and dependencies
 *      - If module is already downloaded, check if the version is up-to-date and show update button
 *      - If module is already downloaded, show remove button
 *      - If module is already downloaded, show enable / disable button
 *      - If install is selected
 *        - Check if ModuleDependencies are present
 *          - If not check if they can be downloaded
 *            - If they can, offer a Modal to let user accept the download of all required modules
 *            - If they can not, show a Modal to indicate which modules are not available
 *          - If they are, download Module
 */

class ModuleShop : public IModule {
  CMM* m_pCMM = nullptr;

  std::string m_sListString;
  int32_t m_i32ListSelection = -1;
  int32_t m_i32PrevListSelection = -1;
  std::vector<ModuleWrapper<IModule>*> m_LocalModules;

  void drawModuleTypeSelector(float& i_fX, float& i_fY);
  void drawModuleSearch(float& i_fX, float& i_fY);
  void drawModuleCounts(float& i_fX, float& i_fY);
  void drawSettingsButton(float& i_fX, float& i_fY);
  void drawModuleList(float& i_fX, float& i_fY);
  void drawModuleView(float& i_fX, float& i_fY);

public:
  ModuleShop();

  void draw(float i_fX, float i_fY) override;
};

#endif // CARPI_MODULES_MODULESHOP_MODULESHOP_H_
