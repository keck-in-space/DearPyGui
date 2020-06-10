#pragma once

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <string>
#include <vector>
#include <imgui.h>
#include "mvCore.h"

//-----------------------------------------------------------------------------
// Helper Macros
//-----------------------------------------------------------------------------
#define MV_APPITEM_TYPE(x) virtual mvAppItemType getType() const override { return x; }

namespace Marvel {

	//-----------------------------------------------------------------------------
	// Enums
	//-----------------------------------------------------------------------------
	enum class mvAppItemType
	{
		None = 0, Spacing, SameLine,
		InputText, Button, RadioButtons,
		TabBar, TabItem, EndTabItem, EndTabBar,
		MenuBar, Menu, EndMenu, MenuItem, EndMenuBar,
		Group, EndGroup, Child, EndChild,
		Tooltip, EndTooltip, CollapsingHeader, EndCollapsingHeader,
		Separator, ColorEdit4, Checkbox, InputInt, InputFloat,
		Listbox, Text, LabelText, Combo, Plot, SimplePlot,
		Indent, Unindent, Drawing, Window, EndWindow,
		Popup, EndPopup
	};

	//-----------------------------------------------------------------------------
	// mvAppItem
	//-----------------------------------------------------------------------------
	class mvAppItem
	{

	public:

		mvAppItem(const std::string& parent, const std::string& name);

		~mvAppItem() = default;

		mvAppItem(const mvAppItem& other) = delete;
		mvAppItem(mvAppItem&& other) = delete;
		mvAppItem operator=(const mvAppItem& other) = delete;
		mvAppItem operator=(mvAppItem&& other) = delete;

		virtual void          setPyValue(PyObject* value) = 0;
		virtual PyObject*     getPyValue() const = 0;
		virtual mvAppItemType getType   () const = 0;
		virtual void          draw      () = 0;

		inline const std::string&       getName    () const { return m_name; }
		inline const std::string&       getTip     () const { return m_tip; }
		inline std::vector<mvAppItem*>& getChildren() { return m_children; }
		inline mvAppItem*               getParent  () { return m_parent; }
		inline const std::string&       getCallback() { return m_callback; }
		inline const std::string&       getPopup   () { return m_popup; }
		inline int                      getWidth   () const { return m_width; }
		inline bool                     isShown    () const { return m_show; }
		inline void                     show       () { m_show = true; }
		inline void                     hide       () { m_show = false; }
		inline void                     setCallback(const std::string& callback) { m_callback = callback; }
		inline void                     setPopup   (const std::string& popup) { m_popup = popup; }
		inline void                     setTip     (const std::string& tip) { m_tip = tip; }
		inline void                     setWidth   (int width) { m_width = width; }
		void                            showAll    ();
		void                            hideAll    ();

		// utilities
		bool isItemHovered() const { return m_hovered; }
		bool isItemActive() const { return m_active; }
		bool isItemFocused() const { return m_focused; }
		bool isItemClicked() const { return m_clicked; }
		bool isItemVisible() const { return m_visible; }
		bool isItemEdited() const { return m_edited; }
		bool isItemActivated() const { return m_activated; }
		bool isItemDeactivated() const { return m_deactivated; }
		bool isItemDeactivatedAfterEdit() const { return m_deactivatedAfterEdit; }
		bool isItemToogledOpen() const { return m_toggledOpen; }
		mvVec2 getItemRectMin() const { return m_rectMin; }
		mvVec2 getItemRectMax() const { return m_rectMax; }
		mvVec2 getItemRectSize() const { return m_rectSize; }


		void setHovered(bool value) { m_hovered = value; }
		void setActive(bool value) { m_active = value; }
		void setFocused(bool value) { m_focused = value; }
		void setClicked(bool value) { m_clicked = value; }
		void setVisible(bool value) { m_visible = value; }
		void setEdited(bool value) { m_edited = value; }
		void setActivated(bool value) { m_activated = value; }
		void setDeactivated(bool value) { m_deactivated = value; }
		void setDeactivatedAfterEdit(bool value) { m_deactivatedAfterEdit = value; }
		void setToggledOpen(bool value) { m_toggledOpen = value; }

		void setRectMin(mvVec2 value) { m_rectMin = value; }
		void setRectMax(mvVec2 value) { m_rectMax = value; }
		void setRectSize(mvVec2 value) { m_rectSize = value; }

	protected:

		int                     m_width = 0;
		std::string             m_name;
		std::string             m_popup;
		std::string             m_label;
		std::string             m_tip;
		bool                    m_show;
		mvAppItem*              m_parent = nullptr;
		std::vector<mvAppItem*> m_children;
		std::string             m_callback = "";

		bool m_hovered;
		bool m_active;
		bool m_focused;
		bool m_clicked;
		bool m_visible;
		bool m_edited;
		bool m_activated;
		bool m_deactivated;
		bool m_deactivatedAfterEdit;
		bool m_toggledOpen;
		mvVec2 m_rectMin;
		mvVec2 m_rectMax;
		mvVec2 m_rectSize;

	};

}