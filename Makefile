include $(TOPDIR)/rules.mk

PKG_NAME:=ltauth
PKG_RELEASE:=1.0
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

 
define Package/ltauth

	SECTION:=utils

	CATEGORY:=Utilities

	TITLE:=ltauth -- prints a snarky message

endef

define Package/ltauth/description

    联通认证客户端.

endef

define Build/Prepare   #已修正

	echo "Here is Package/Prepare"

	mkdir -p $(PKG_BUILD_DIR)

	$(CP) ./src/* $(PKG_BUILD_DIR)/

endef

define Package/ltauth/install

	echo "Here is Package/install"

	$(INSTALL_DIR) $(1)/bin

	$(INSTALL_BIN) $(PKG_BUILD_DIR)/ltauth $(1)/bin/

endef

$(eval $(call BuildPackage,ltauth))
