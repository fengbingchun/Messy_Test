/*

   ____                               ____      ___ ____       ____  ____      ___
  6MMMMb                              `MM(      )M' `MM'      6MMMMb\`MM(      )M'
 8P    Y8                              `MM.     d'   MM      6M'    ` `MM.     d'
6M      Mb __ ____     ____  ___  __    `MM.   d'    MM      MM        `MM.   d'
MM      MM `M6MMMMb   6MMMMb `MM 6MMb    `MM. d'     MM      YM.        `MM. d'
MM      MM  MM'  `Mb 6M'  `Mb MMM9 `Mb    `MMd       MM       YMMMMb     `MMd
MM      MM  MM    MM MM    MM MM'   MM     dMM.      MM           `Mb     dMM.
MM      MM  MM    MM MMMMMMMM MM    MM    d'`MM.     MM            MM    d'`MM.
YM      M9  MM    MM MM       MM    MM   d'  `MM.    MM            MM   d'  `MM.
 8b    d8   MM.  ,M9 YM    d9 MM    MM  d'    `MM.   MM    / L    ,M9  d'    `MM.
  YMMMM9    MMYMMM9   YMMMM9 _MM_  _MM_M(_    _)MM_ _MMMMMMM MYMMMM9 _M(_    _)MM_
            MM
            MM
           _MM_

  Copyright (c) 2018, Kenneth Troldal Balslev

  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
  - Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
  - Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
  - Neither the name of the author nor the
    names of any contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */

#ifndef OPENXLSX_XLSHEET_HPP
#define OPENXLSX_XLSHEET_HPP

#ifdef _MSC_VER    // conditionally enable MSVC specific pragmas to avoid other compilers warning about unknown pragmas
#   pragma warning(push)
#   pragma warning(disable : 4251)
#   pragma warning(disable : 4275)
#endif // _MSC_VER

// ===== External Includes ===== //
#include <cstdint>      // uint8_t, uint16_t, uint32_t
#include <ostream>      // std::basic_ostream
#include <string_view>  // std::string_view
#include <type_traits>
#include <variant>
#include <vector>       // std::vector< std::string_view >

// ===== OpenXLSX Includes ===== //
#include "OpenXLSX-Exports.hpp"
#include "XLCell.hpp"
#include "XLCellRange.hpp"
#include "XLCellReference.hpp"
#include "XLColor.hpp"
#include "XLColumn.hpp"
#include "XLCommandQuery.hpp"
#include "XLComments.hpp" // XLComments
#include "XLDocument.hpp"
#include "XLException.hpp"
#include "XLMergeCells.hpp"
#include "XLRow.hpp"
#include "XLStyles.hpp"   // XLStyleIndex
#include "XLTables.hpp"   // XLTables
#include "XLXmlFile.hpp"

namespace OpenXLSX
{
    constexpr const bool XLEmptyHiddenCells = true; // readability constant for XLWorksheet::mergeCells parameter emptyHiddenCells

    /**
     * @brief The XLSheetState is an enumeration of the possible (visibility) states, e.g. Visible or Hidden.
     */
    enum class XLSheetState : uint8_t { Visible, Hidden, VeryHidden };

    constexpr const uint16_t XLPriorityNotSet = 0; // readability constant for XLCfRule::priority()

    enum class XLCfType : uint8_t {
        Expression        =   0,
        CellIs            =   1,
        ColorScale        =   2,
        DataBar           =   3,
        IconSet           =   4,
        Top10             =   5,
        UniqueValues      =   6,
        DuplicateValues   =   7,
        ContainsText      =   8,
        NotContainsText   =   9,
        BeginsWith        =  10,
        EndsWith          =  11,
        ContainsBlanks    =  12,
        NotContainsBlanks =  13,
        ContainsErrors    =  14,
        NotContainsErrors =  15,
        TimePeriod        =  16,
        AboveAverage      =  17,
        Invalid           = 255
    };

    enum class XLCfOperator : uint8_t {
        LessThan           =   0,
        LessThanOrEqual    =   1,
        Equal              =   2,
        NotEqual           =   3,
        GreaterThanOrEqual =   4,
        GreaterThan        =   5,
        Between            =   6,
        NotBetween         =   7,
        ContainsText       =   8,
        NotContains        =   9,
        BeginsWith         =  10,
        EndsWith           =  11,
        Invalid            = 255
    };

    enum class XLCfTimePeriod : uint8_t {
        Today     =   0,
        Yesterday =   1,
        Tomorrow  =   2,
        Last7Days =   3,
        ThisMonth =   4,
        LastMonth =   5,
        NextMonth =   6,
        ThisWeek  =   7,
        LastWeek  =   8,
        NextWeek  =   9,
        Invalid   = 255
    };

    const std::vector< std::string_view > XLWorksheetNodeOrder = {      // worksheet XML root node required child sequence
            "sheetPr",
            "dimension",
            "sheetViews",
            "sheetFormatPr",
            "cols",
            "sheetData",
            "sheetCalcPr",
            "sheetProtection",
            "protectedRanges",
            "scenarios",
            "autoFilter",
            "sortState",
            "dataConsolidate",
            "customSheetViews",
            "mergeCells",
            "phoneticPr",
            "conditionalFormatting",
            "dataValidations",
            "hyperlinks",
            "printOptions",
            "pageMargins",
            "pageSetup",
            "headerFooter",
            "rowBreaks",
            "colBreaks",
            "customProperties",
            "cellWatches",
            "ignoredErrors",
            "smartTags",
            "drawing",
            "legacyDrawing",
            "legacyDrawingHF",
            "picture",
            "oleObjects",
            "controls",
            "webPublishItems",
            "tableParts",
            "extLst"
    }; // END: const std::vector< std::string_view > XLWorksheetNodeOrder

    // ================================================================================
    // Converter functions between OpenXLSX class specific enum class types and OOXML values
    // ================================================================================
    OPENXLSX_EXPORT XLCfType       XLCfTypeFromString      (std::string const& typeString      );
    OPENXLSX_EXPORT std::string    XLCfTypeToString        (XLCfType           cfType          );
    OPENXLSX_EXPORT XLCfOperator   XLCfOperatorFromString  (std::string const& operatorString  );
    OPENXLSX_EXPORT std::string    XLCfOperatorToString    (XLCfOperator       cfOperator      );
    OPENXLSX_EXPORT XLCfTimePeriod XLCfTimePeriodFromString(std::string const& timePeriodString);
    OPENXLSX_EXPORT std::string    XLCfTimePeriodToString  (XLCfTimePeriod     cfTimePeriod    );

    /**
     * @brief The XLSheetBase class is the base class for the XLWorksheet and XLChartsheet classes. However,
     * it is not a base class in the traditional sense. Rather, it provides common functionality that is
     * inherited via the CRTP (Curiously Recurring Template Pattern) pattern.
     * @tparam T Type that will inherit functionality. Restricted to types XLWorksheet and XLChartsheet.
     */
    template<typename T, typename = std::enable_if_t<std::is_same_v<T, XLWorksheet> || std::is_same_v<T, XLChartsheet>>>
    class OPENXLSX_EXPORT XLSheetBase : public XLXmlFile
    {
    public:
        /**
         * @brief Constructor
         */
        XLSheetBase() : XLXmlFile(nullptr) {};

        /**
         * @brief The constructor. There are no default constructor, so all parameters must be provided for
         * constructing an XLAbstractSheet object. Since this is a pure abstract class, instantiation is only
         * possible via one of the derived classes.
         * @param xmlData
         */
        explicit XLSheetBase(XLXmlData* xmlData) : XLXmlFile(xmlData) {}

        /**
         * @brief The copy constructor.
         * @param other The object to be copied.
         * @note The default copy constructor is used, i.e. only shallow copying of pointer data members.
         */
        XLSheetBase(const XLSheetBase& other) = default;

        /**
         * @brief
         * @param other
         */
        XLSheetBase(XLSheetBase&& other) noexcept = default;

        /**
         * @brief The destructor
         * @note The default destructor is used, since cleanup of pointer data members is not required.
         */
        ~XLSheetBase() = default;

        /**
         * @brief Assignment operator
         * @return A reference to the new object.
         * @note The default assignment operator is used, i.e. only shallow copying of pointer data members.
         */
        XLSheetBase& operator=(const XLSheetBase&) = default;

        /**
         * @brief
         * @param other
         * @return
         */
        XLSheetBase& operator=(XLSheetBase&& other) noexcept = default;

        /**
         * @brief
         * @return
         */
        XLSheetState visibility() const
        {
            XLQuery query(XLQueryType::QuerySheetVisibility);
            query.setParam("sheetID", relationshipID());
            const auto state  = parentDoc().execQuery(query).template result<std::string>();
            auto result = XLSheetState::Visible;

            if (state == "visible" || state.empty()) {
                result = XLSheetState::Visible;
            }
            else if (state == "hidden") {
                result = XLSheetState::Hidden;
            }
            else if (state == "veryHidden") {
                result = XLSheetState::VeryHidden;
            }

            return result;
        }

        /**
         * @brief
         * @param state
         */
        void setVisibility(XLSheetState state)
        {
            auto stateString = std::string();
            switch (state) {
                case XLSheetState::Visible:
                    stateString = "visible";
                    break;

                case XLSheetState::Hidden:
                    stateString = "hidden";
                    break;

                case XLSheetState::VeryHidden:
                    stateString = "veryHidden";
                    break;
            }

            parentDoc().execCommand(XLCommand(XLCommandType::SetSheetVisibility)
                                        .setParam("sheetID", relationshipID())
                                        .setParam("sheetVisibility", stateString));
        }

        /**
         * @brief
         * @return
         * @todo To be implemented.
         */
        XLColor color() const
        {
            return static_cast<const T&>(*this).getColor_impl();
        }

        /**
         * @brief
         * @param color
         */
        void setColor(const XLColor& color)
        {
            static_cast<T&>(*this).setColor_impl(color);
        }

        /**
         * @brief look up sheet name via relationshipID, then attempt to match that to a sheet in XLWorkbook::sheet(uint16_t index), looping over index
         * @return the index by which the sheet could be accessed from XLWorkbook::sheet
         */
        uint16_t index() const
        {
            XLQuery query(XLQueryType::QuerySheetIndex);
            query.setParam("sheetID", relationshipID());
            return static_cast<uint16_t>(std::stoi(parentDoc().execQuery(query).template result<std::string>()));
        }

        /**
         * @brief
         * @param index
         */
        void setIndex(uint16_t index)
        {
            parentDoc().execCommand(XLCommand(XLCommandType::SetSheetIndex)
                                        .setParam("sheetID", relationshipID())
                                        .setParam("sheetIndex", index));
        }

        /**
         * @brief Method to retrieve the name of the sheet.
         * @return A std::string with the sheet name.
         */
        std::string name() const
        {
            XLQuery query(XLQueryType::QuerySheetName);
            query.setParam("sheetID", relationshipID());
            return parentDoc().execQuery(query).template result<std::string>();
        }

        /**
         * @brief Method for renaming the sheet.
         * @param sheetName A std::string with the new name.
         */
        void setName(const std::string& sheetName)
        {
            parentDoc().execCommand(XLCommand(XLCommandType::SetSheetName)
                                        .setParam("sheetID", relationshipID())
                                        .setParam("sheetName", name())
                                        .setParam("newName", sheetName));
        }

        /**
         * @brief
         * @return
         */
        bool isSelected() const
        {
            return static_cast<const T&>(*this).isSelected_impl();
        }

        /**
         * @brief
         * @param selected
         */
        void setSelected(bool selected)
        {
            static_cast<T&>(*this).setSelected_impl(selected);
        }

        /**
         * @brief
         * @return
         */
        bool isActive() const
        {
            return static_cast<const T&>(*this).isActive_impl();
        }

        /**
         * @brief
         */
        bool setActive()
        {
            return static_cast<T&>(*this).setActive_impl();
        }

        /**
         * @brief Method for cloning the sheet.
         * @param newName A std::string with the name of the clone
         * @return A pointer to the cloned object.
         * @note This is a pure abstract method. I.e. it is implemented in subclasses.
         */
        void clone(const std::string& newName)
        {
            parentDoc().execCommand(XLCommand(XLCommandType::CloneSheet)
                                        .setParam("sheetID", relationshipID())
                                        .setParam("cloneName", newName));
        }

    private:   // ---------- Private Member Variables ---------- //
    };


    // ================================================================================
    // XLConditionalFormats Class
    // ================================================================================

    /**
     * @brief An encapsulation of a cfRule item
     */
    class OPENXLSX_EXPORT XLCfRule
    {
        friend class XLCfRules;    // for access to m_cfRuleNode in XLCfRules::create
    public:    // ---------- Public Member Functions ---------- //
        /**
         * @brief
         */
        XLCfRule();

        /**
         * @brief Constructor. New items should only be created through an XLCfRules object.
         * @param node An XMLNode object with the <cfRule> item. If no input is provided, a null node is used.
         */
        explicit XLCfRule(const XMLNode& node);

        /**
         * @brief Copy Constructor.
         * @param other Object to be copied.
         */
        XLCfRule(const XLCfRule& other);

        /**
         * @brief Move Constructor.
         * @param other Object to be moved.
         */
        XLCfRule(XLCfRule&& other) noexcept = default;

        /**
         * @brief
         */
        ~XLCfRule();

        /**
         * @brief Copy assignment operator.
         * @param other Right hand side of assignment operation.
         * @return A reference to the lhs object.
         */
        XLCfRule& operator=(const XLCfRule& other);

        /**
         * @brief Move assignment operator.
         * @param other Right hand side of assignment operation.
         * @return A reference to lhs object.
         */
        XLCfRule& operator=(XLCfRule&& other) noexcept = default;

        /**
         * @brief Test if this is an empty node
         * @return true if underlying XMLNode is empty
         */
        bool empty() const;

        /**
         * @brief Element getter functions
         */
        std::string formula() const;
        XLUnsupportedElement colorScale() const;
        XLUnsupportedElement dataBar()    const;
        XLUnsupportedElement iconSet()    const;
        XLUnsupportedElement extLst()     const;

        /**
         * @brief Attribute getter functions
         */

        XLCfType type() const;
        XLStyleIndex dxfId() const;
        uint16_t priority() const; // >= 1
        bool stopIfTrue() const;   // default: false
        bool aboveAverage() const; // default: true
        bool percent() const; // default: false
        bool bottom() const; // default: false
        XLCfOperator Operator() const; // Valid only when @type = cellIs
        std::string text() const; // The text value in a "text contains" conditional formatting rule. Valid only for @type = containsText.
        XLCfTimePeriod timePeriod() const; // The applicable time period in a "date occurring..." conditional formatting rule. Valid only for @type = timePeriod.
        uint16_t rank() const; // The value of "n" in a "top/bottom n" conditional formatting rule. Valid only for @type = top10.
        int16_t stdDev() const; // The number of standard deviations to include above or below the average in the conditional formatting rule. Valid only for @type = aboveAverage
        bool equalAverage() const; // default: false. Flag indicating whether the 'aboveAverage' and 'belowAverage' criteria
        //                             is inclusive of the average itself, or exclusive of that value. '1' indicates to include
        //                             the average value in the criteria. Valid only for @type = aboveAverage.

        /**
         * @brief Element setter functions
         */
        bool setFormula   (std::string const& newFormula);
        bool setColorScale(XLUnsupportedElement const& newColorScale); // unsupported
        bool setDataBar   (XLUnsupportedElement const& newDataBar   ); // unsupported
        bool setIconSet   (XLUnsupportedElement const& newIconSet   ); // unsupported
        bool setExtLst    (XLUnsupportedElement const& newExtLst    ); // unsupported

        /**
         * @brief Attribute setter functions
         */
        bool setType(XLCfType newType);
        bool setDxfId(XLStyleIndex newDxfId);
    private: // Protect setPriority from access by any but the parent XLCfRules class
        bool setPriority(uint16_t newPriority); // internal function, user access through XLCfRules::setPriority
    public:
        bool setStopIfTrue(bool set = true);
        bool setAboveAverage(bool set = true);
        bool setPercent(bool set = true);
        bool setBottom(bool set = true);
        bool setOperator(XLCfOperator newOperator);
        bool setText(std::string const& newText);
        bool setTimePeriod(XLCfTimePeriod newTimePeriod);
        bool setRank(uint16_t newRank);
        bool setStdDev(int16_t newStdDev);
        bool setEqualAverage(bool set = true);

        /**
         * @brief Return a string summary of the cfRule properties
         * @return string with info about the cfRule object
         */
        std::string summary() const;

    private:                                    // ---------- Private Member Variables ---------- //
        std::unique_ptr<XMLNode> m_cfRuleNode;  /**< An XMLNode object with the conditional formatting item */
        inline static const std::vector< std::string_view > m_nodeOrder = {      // cfRule XML node required child sequence
            "formula", // TODO: maxOccurs = 3!
            "colorScale",
            "dataBar",
            "iconSet",
            "extLst"
        };
    };


    constexpr const char * XLDefaultCfRulePrefix = "\n\t\t"; // indentation to use for newly created cfRule nodes
    /**
     * @brief An encapsulation of a conditional formatting rules item
     */
    class OPENXLSX_EXPORT XLCfRules
    {
    public:
        /**
         * @brief
         */
        XLCfRules();

        /**
         * @brief Constructor. New items should only be created through an XLConditionalFormat object.
         * @param node An XMLNode object with the conditionalFormatting item. If no input is provided, a null node is used.
         */
        explicit XLCfRules(const XMLNode& node);

        /**
         * @brief Copy Constructor.
         * @param other Object to be copied.
         */
        XLCfRules(const XLCfRules& other);

        /**
         * @brief Move Constructor.
         * @param other Object to be moved.
         */
        XLCfRules(XLCfRules&& other) noexcept = default;

        /**
         * @brief
         */
        ~XLCfRules();

        /**
         * @brief Copy assignment operator.
         * @param other Right hand side of assignment operation.
         * @return A reference to the lhs object.
         */
        XLCfRules& operator=(const XLCfRules& other);

        /**
         * @brief Move assignment operator.
         * @param other Right hand side of assignment operation.
         * @return A reference to lhs object.
         */
        XLCfRules& operator=(XLCfRules&& other) noexcept = default;

        /**
         * @brief Test if this is an empty node
         * @return true if underlying XMLNode is empty
         */
        bool empty() const;

        /**
         * @brief Get the count highest priority value currently in use by a rule
         * @return The highest value that a cfRule has set for attribute priority
         */
        uint16_t maxPriorityValue() const;

        /**
         * @brief Provide a duplication-free interface to setting rule priorities: if a newPriority value exists, increment all existing priorities >= newPriority by 1
         * @param cfRuleIndex the index of the rule for which to set the priority
         * @param newPriority the priority value to assign
         * @return true on success, false if ruleIndex does not exist
         */
        bool setPriority(size_t cfRuleIndex, uint16_t newPriority);

        /**
         * @brief Renumber all existing rule priorities to a clean sequence in steps of increment
         * @param increment increase the priority value by this much between rules
         */
        void renumberPriorities(uint16_t increment = 1);

        /**
         * @brief Get the count of rules for this conditional formatting
         * @return The amount of <cfRule> nodes in the <conditionalFormatting> node
         */
        size_t count() const;

        /**
         * @brief Get the conditional format identified by index
         * @return An XLCfRule object
         */
        XLCfRule cfRuleByIndex(size_t index) const;

        /**
         * @brief Operator overload: allow [] as shortcut access to cfRuleByIndex
         * @param index The index within the XML sequence
         * @return An XLCfRule object
         */
        XLCfRule operator[](size_t index) const { return cfRuleByIndex(index); }

        /**
         * @brief Append a new XLCfRule, based on copyFrom, and return its index in the <conditionalFormatting> list of <cfRule> entries
         * @param copyFrom Can provide an XLCfRule to use as template for the new condition
         * @param conditionalFormattingPrefix Prefix the newly created conditionalFormatting XMLNode with this pugi::node_pcdata text
         * @returns The index of the new conditional formatting as used by operator[]
         */
        size_t create(XLCfRule copyFrom = XLCfRule{}, std::string cfRulePrefix = XLDefaultCfRulePrefix);

        /**
         * @brief Return a string summary of the conditional formatting rules properties
         * @return string with info about the conditional formatting rules object
         */
        std::string summary() const;

    private:                                                   // ---------- Private Member Variables ---------- //
        std::unique_ptr<XMLNode> m_conditionalFormattingNode;  /**< An XMLNode object with the conditional formatting item */
        // TODO: pass in m_nodeOrder from XLConditionalFormat
        inline static const std::vector< std::string_view > m_nodeOrder = {      // conditionalFormatting XML node required child sequence
            "cfRule",
            "extLst"
        };
    };


    /**
     * @brief An encapsulation of a conditional formatting item
     */
    class OPENXLSX_EXPORT XLConditionalFormat
    {
        friend class XLConditionalFormats;    // for access to m_conditionalFormattingNode in XLConditionalFormats::create
    public:    // ---------- Public Member Functions ---------- //
        /**
         * @brief
         */
        XLConditionalFormat();

        /**
         * @brief Constructor. New items should only be created through an XLWorksheet object.
         * @param node An XMLNode object with the conditionalFormatting item. If no input is provided, a null node is used.
         */
        explicit XLConditionalFormat(const XMLNode& node);

        /**
         * @brief Copy Constructor.
         * @param other Object to be copied.
         */
        XLConditionalFormat(const XLConditionalFormat& other);

        /**
         * @brief Move Constructor.
         * @param other Object to be moved.
         */
        XLConditionalFormat(XLConditionalFormat&& other) noexcept = default;

        /**
         * @brief
         */
        ~XLConditionalFormat();

        /**
         * @brief Copy assignment operator.
         * @param other Right hand side of assignment operation.
         * @return A reference to the lhs object.
         */
        XLConditionalFormat& operator=(const XLConditionalFormat& other);

        /**
         * @brief Move assignment operator.
         * @param other Right hand side of assignment operation.
         * @return A reference to lhs object.
         */
        XLConditionalFormat& operator=(XLConditionalFormat&& other) noexcept = default;

        /**
         * @brief Test if this is an empty node
         * @return true if underlying XMLNode is empty
         */
        bool empty() const;

        /**
         * @brief Get the sqref property - the range over which these conditional formatting rules apply
         * @return string of the sqref property
         */
        std::string sqref() const;

        /**
         * @brief Get the conditional formatting rules to be applied to sqref
         * @return the conditional formatting rules applicable to sqref
         */
        XLCfRules cfRules() const;


        /**
         * @brief Unsupported getter
         */
        XLUnsupportedElement extLst() const { return XLUnsupportedElement{}; } // <conditionalFormatting><extLst>...</extLst></conditionalFormatting>

        /**
         * @brief Setter functions for conditional formatting parameters
         * @param value that shall be set
         * @return true for success, false for failure
         */
        bool setSqref        (std::string newSqref);

        /**
         * @brief Unsupported setter
         */
        bool setExtLst   (XLUnsupportedElement const& newExtLst);

        /**
         * @brief Return a string summary of the conditional format properties
         * @return string with info about the conditional formatting object
         */
        std::string summary() const;

    private:                                                   // ---------- Private Member Variables ---------- //
        std::unique_ptr<XMLNode> m_conditionalFormattingNode;  /**< An XMLNode object with the conditional formatting item */
        inline static const std::vector< std::string_view > m_nodeOrder = {   // conditionalFormatting XML node required child sequence
            "cfRule",
            "extLst"
        };
    };


    constexpr const char * XLDefaultConditionalFormattingPrefix = "\n\t"; // indentation to use for newly created conditional formatting nodes
    /**
     * @brief An encapsulation of the XLSX conditional formats
     */
    class OPENXLSX_EXPORT XLConditionalFormats
    {
    public:    // ---------- Public Member Functions ---------- //
        /**
         * @brief
         */
        XLConditionalFormats();

        /**
         * @brief Constructor. New items should only be created through an XLWorksheet object.
         * @param node An XMLNode object with the worksheet root node. Required to access / manipulate any conditional formats
         */
        explicit XLConditionalFormats(const XMLNode& node);

        /**
         * @brief Copy Constructor.
         * @param other Object to be copied.
         */
        XLConditionalFormats(const XLConditionalFormats& other);

        /**
         * @brief Move Constructor.
         * @param other Object to be moved.
         */
        XLConditionalFormats(XLConditionalFormats&& other);

        /**
         * @brief
         */
        ~XLConditionalFormats();

        /**
         * @brief Copy assignment operator.
         * @param other Right hand side of assignment operation.
         * @return A reference to the lhs object.
         */
        XLConditionalFormats& operator=(const XLConditionalFormats& other);

        /**
         * @brief Move assignment operator.
         * @param other Right hand side of assignment operation.
         * @return A reference to lhs object.
         */
        XLConditionalFormats& operator=(XLConditionalFormats&& other) noexcept = default;

        /**
         * @brief Test if this is an empty node
         * @return true if underlying XMLNode is empty
         */
        bool empty() const;

        /**
         * @brief Get the count of conditional formatting settings
         * @return The amount of <conditionalFormatting> nodes in the worksheet
         */
        size_t count() const;

        /**
         * @brief Get the conditional format identified by index
         * @return An XLConditionalFormat object
         */
        XLConditionalFormat conditionalFormatByIndex(size_t index) const;

        /**
         * @brief Operator overload: allow [] as shortcut access to conditionalFormatByIndex
         * @param index The index within the XML sequence
         * @return An XLConditionalFormat object
         */
        XLConditionalFormat operator[](size_t index) const { return conditionalFormatByIndex(index); }

        /**
         * @brief Append a new XLConditionalFormat, based on copyFrom, and return its index in the worksheet's conditional formats
         * @param copyFrom Can provide an XLConditionalFormat to use as template for the new condition
         * @param conditionalFormattingPrefix Prefix the newly created conditionalFormatting XMLNode with this pugi::node_pcdata text
         * @returns The index of the new conditional formatting as used by operator[]
         */
        size_t create(XLConditionalFormat copyFrom = XLConditionalFormat{}, std::string conditionalFormattingPrefix = XLDefaultConditionalFormattingPrefix);

        /**
         * @brief Return a string summary of the conditional formattings properties
         * @return string with info about the conditional formattings object
         */
        std::string summary() const;

    private:                                    // ---------- Private Member Variables ---------- //
        std::unique_ptr<XMLNode> m_sheetNode;   /**< An XMLNode object with the sheet item */
        const std::vector< std::string_view >& m_nodeOrder = XLWorksheetNodeOrder;  // worksheet XML root node required child sequence
    };

    /**
     * @brief A class encapsulating an Excel worksheet. Access to XLWorksheet objects should be via the workbook object.
     */
    class OPENXLSX_EXPORT XLWorksheet final : public XLSheetBase<XLWorksheet>
    {
        friend class XLCell;
        friend class XLRow;
        friend class XLWorkbook;
        friend class XLSheetBase<XLWorksheet>;

        //----------------------------------------------------------------------------------------------------------------------
        //           Public Member Functions
        //----------------------------------------------------------------------------------------------------------------------

    public:
        /**
         * @brief Default constructor
         */
        XLWorksheet() : XLSheetBase(nullptr) {};

        /**
         * @brief
         * @param xmlData
         */
        explicit XLWorksheet(XLXmlData* xmlData);

        /**
         * @brief Destructor.
         */
        ~XLWorksheet() = default;

        /**
         * @brief Copy Constructor.
         */
        XLWorksheet(const XLWorksheet& other);

        /**
         * @brief Move Constructor.
         */
        XLWorksheet(XLWorksheet&& other);

        /**
         * @brief Copy assignment operator.
         */
        XLWorksheet& operator=(const XLWorksheet& other);

        /**
         * @brief Move assignment operator.
         */
        XLWorksheet& operator=(XLWorksheet&& other);

        /**
         * @brief
         * @param ref
         * @return
         */
        XLCellAssignable cell(const std::string& ref) const;

        /**
         * @brief Get an XLCell object for the given cell reference.
         * @param ref An XLCellReference object with the address of the cell to get.
         * @return A reference to the requested XLCell object.
         */
        XLCellAssignable cell(const XLCellReference& ref) const;

        /**
         * @brief Get the cell at the given coordinates. Create row & cell XML if missing.
         * @param rowNumber The row number (index base 1).
         * @param columnNumber The column number (index base 1).
         * @return A reference to the XLCell object at the given coordinates.
         */
        XLCellAssignable cell(uint32_t rowNumber, uint16_t columnNumber) const;

        /**
         * @brief overload for findCell(uint32_t rowNumber, uint16_t columnNumber)
         * @param ref string with the address of the cell to find
         * @return
         */
        XLCellAssignable findCell(const std::string& ref) const;

        /**
         * @brief overload for findCell(uint32_t rowNumber, uint16_t columnNumber)
         * @param ref An XLCellReference object with the address of the cell to find
         * @return
         */
        XLCellAssignable findCell(const XLCellReference& ref) const;

        /**
         * @brief Find the cell at the given coordinates. Do *not* create row & cell XML if missing and return an empty XLCellAssignable instead
         * @param rowNumber The row number (index base 1).
         * @param columnNumber The column number (index base 1).
         * @return A reference to the XLCell object at the given coordinates or an empty XLCell object
         * @note Must test (XLCell::empty() == false) before accessing any other methods of the returned object.
         * @warning This is a usability feature with bad performance. When testing a large amounts of cells or working with large worksheets,
         *           it is better to use an XLCellIterator with the cell range of interest.
         */
        XLCellAssignable findCell(uint32_t rowNumber, uint16_t columnNumber) const;

        /**
         * @brief Get a range for the area currently in use (i.e. from cell A1 to the last cell being in use).
         * @return An XLCellRange object with the entire range.
         */
        XLCellRange range() const;

        /**
         * @brief Get a range with the given coordinates.
         * @param topLeft An XLCellReference object with the coordinates to the top left cell.
         * @param bottomRight An XLCellReference object with the coordinates to the bottom right cell.
         * @return An XLCellRange object with the requested range.
         */
        XLCellRange range(const XLCellReference& topLeft, const XLCellReference& bottomRight) const;

        /**
         * @brief Get a range with the given coordinates.
         * @param topLeft A std::string that is convertible to an XLCellReference to the top left cell
         * @param bottomRight A std::string that is convertible to an XLCellReference to the bottom right cell.
         * @return An XLCellRange object with the requested range.
         */
        XLCellRange range(std::string const& topLeft, std::string const& bottomRight) const;

        /**
         * @brief Get a range with the given coordinates.
         * @param rangeReference A std::string that contains two XLCellReferences separated by a delimiter ':'
         *                       Example "A2:B5"
         * @return An XLCellRange object with the requested range.
         */
        XLCellRange range(std::string const& rangeReference) const;

        /**
         * @brief
         * @return
         */
        XLRowRange rows() const;

        /**
         * @brief
         * @param rowCount
         * @return
         */
        XLRowRange rows(uint32_t rowCount) const;

        /**
         * @brief
         * @param firstRow
         * @param lastRow
         * @return
         */
        XLRowRange rows(uint32_t firstRow, uint32_t lastRow) const;

        /**
         * @brief Get the row with the given row number.
         * @param rowNumber The number of the row to retrieve.
         * @return A reference to the XLRow object.
         */
        XLRow row(uint32_t rowNumber) const;

        /**
         * @brief Get the column with the given column number.
         * @param columnNumber The number of the column to retrieve.
         * @return A reference to the XLColumn object.
         */
        XLColumn column(uint16_t columnNumber) const;

        /**
         * @brief Get the column with the given column reference
         * @param columnRef The letters referencing the given column
         * @return A reference to the XLColumn object.
         */
        XLColumn column(std::string const& columnRef) const;

        /**
         * @brief Get an XLCellReference to the last (bottom right) cell in the worksheet.
         * @return An XLCellReference for the last cell.
         */
        XLCellReference lastCell() const noexcept;

        /**
         * @brief Get the number of columns in the worksheet.
         * @return The number of columns.
         */
        uint16_t columnCount() const noexcept;

        /**
         * @brief Get the number of rows in the worksheet.
         * @return The number of rows.
         */
        uint32_t rowCount() const noexcept;

        /**
         * @brief Delete the row with the given row number from the underlying OOXML.
         * @return true if a row entry existed in OOXML & was deleted, otherwise false
         * @warning this will break all existing references to that row (formulas etc)
         */
        bool deleteRow(uint32_t rowNumber);

        /**
         * @brief
         * @param oldName
         * @param newName
         */
        void updateSheetName(const std::string& oldName, const std::string& newName);

        /**
         * @brief get an XLMergeCells object to directly access the member functions
         * @returns an XLMergeCells object for this worksheet
         */
        XLMergeCells & merges();

        /**
         * @brief merge the cells indicated by range
         * @param rangeToMerge the XLCellRange to merge, can be obtained from XLWorksheet::range functions
         * @param emptyHiddenCells if true (XLEmptyHiddenCells), the values of hidden cells will be deleted
         *                         (only from the cells, not from the shared strings table, if used)
         * @throws XLInputException if range comprises < 2 cells or any cell within rangeToMerge is already part of an existing range
         */
        void mergeCells(XLCellRange const& rangeToMerge, bool emptyHiddenCells = false);
        /**
         * @brief Convenience wrapper for mergeCells with a std::string range reference
         * @param rangeReference A range reference string for the cells to merge
         * @param emptyHiddenCells as above
         */
        void mergeCells(const std::string& rangeReference, bool emptyHiddenCells = false);

        /**
         * @brief remove the merge setting for the indicated range
         * @param rangeToUnmerge the XLCellRange to unmerge, can be obtained from XLWorksheet::range functions
         * @throws XLInputException if no merged range exists that matches rangeToMerge precisely
         */
        void unmergeCells(XLCellRange const& rangeToUnmerge);
        /**
         * @brief Convenience wrapper for unmergeCells with a std::string range reference
         * @param rangeReference A range reference string for the cells to unmerge
         */
        void unmergeCells(const std::string& rangeReference);

        /**
         * @brief Get the array index of xl/styles.xml:<styleSheet>:<cellXfs> for the style assigned to a column.
         *        This value is stored in the col attributes like so: style="2"
         * @param column The column letter(s) or index (1-based)
         * @returns The index of the applicable format style
         */
        XLStyleIndex getColumnFormat(uint16_t column) const;
        XLStyleIndex getColumnFormat(const std::string& column) const;

        /**
         * @brief set the column style as a reference to the array index of xl/styles.xml:<styleSheet>:<cellXfs>
         *        Subsequently, set the same style for all existing(!) cells in that column
         * @param column the column letter(s) or index (1-based)
         * @param cellFormatIndex the style to set, corresponding to the index of XLStyles::cellStyles()
         * @returns true on success, false on failure
         */
        bool setColumnFormat(uint16_t column, XLStyleIndex cellFormatIndex);
        bool setColumnFormat(const std::string& column, XLStyleIndex cellFormatIndex);

        /**
         * @brief get the array index of xl/styles.xml:<styleSheet>:<cellXfs> for the style assigned to a row
         *        this value is stored in the row attributes like so: s="2"
         * @param row the row index (1-based)
         * @returns the index of the applicable format style
         */
        XLStyleIndex getRowFormat(uint16_t row) const;

        /**
         * @brief set the row style as a reference to the array index of xl/styles.xml:<styleSheet>:<cellXfs>
         *        Subsequently, set the same style for all existing(!) cells in that row
         * @param row the row index (1-based)
         * @param cellFormatIndex the style to set, corresponding to the index of XLStyles::cellStyles()
         * @returns true on success, false on failure
         */
        bool setRowFormat(uint32_t row, XLStyleIndex cellFormatIndex);

        /**
         * @brief Get the conditional formats object
         * @return An XLConditionalFormats object
         */
        XLConditionalFormats conditionalFormats() const;

        /**
         * @brief Set the <sheetProtection> attributes sheet, objects and scenarios respectively
         * @return true upon success, false in case of any failure
         */
        bool protectSheet(bool set = true);
        bool protectObjects(bool set = true);
        bool protectScenarios(bool set = true);

        /**
         * @brief Set the XML properties that allow the according modification of the worksheet
         * @param set if true, action will be allowed despite sheet protection, if false, action will be denied / protected
         * @note #1 default for all (if attribute is not present) is "true" = the action is protected / not allowed
         * @note #2 none of the sheet protection settings have any effect if protectSheet is not set
         * @note (library internal) counter-intuitively, the underlying bool attributes need to be set to "false" to "disable protection" for these actions
         */
        bool allowInsertColumns(bool set = true);       // default: not allowed in a protected worksheet
        bool allowInsertRows(bool set = true);          //   "    :  "
        bool allowDeleteColumns(bool set = true);       //   "    :  "
        bool allowDeleteRows(bool set = true);          //   "    :  "
        bool allowSelectLockedCells(bool set = true);   // default: allowed in a protected worksheet
        bool allowSelectUnlockedCells(bool set = true); //   "    :  "
        /**
         * @brief Convenience shortcuts for allow<*>( false );
         */
        bool denyInsertColumns()       { return allowInsertColumns      (false); }
        bool denyInsertRows()          { return allowInsertRows         (false); }
        bool denyDeleteColumns()       { return allowDeleteColumns      (false); }
        bool denyDeleteRows()          { return allowDeleteRows         (false); }
        bool denySelectLockedCells()   { return allowSelectLockedCells  (false); }
        bool denySelectUnlockedCells() { return allowSelectUnlockedCells(false); }

        /**
         * @brief Set the sheetProtection password attribute
         * @param hash directly stores a password hash to the password attribute, for use cases where the password shall not be used in clear text in the API
         * @note ExcelPasswordHash or ExcelPasswordHashAsString (defined in XLDocument header) can be used to calculate the hash
         * @note an empty password hash can be used to clear any password protection
         * @return true upon success, false in case of any failure
         */
        bool setPasswordHash(std::string hash);

        /**
         * @brief Set the sheetProtection password attribute
         * @param password the XLSX password hash for this string will be stored in the password attribute
         * @note an empty password clears the password attribute
         * @return true upon success, false in case of any failure
         */
        bool setPassword(std::string password);

        /**
         * @brief Clear the sheetProtection password attribute
         */
        bool clearPassword();

        /**
         * @brief Clear the sheetProtection completely
         */
        bool clearSheetProtection();

        /**
         * @brief getter functions for sheet protection settings
         * @return true if setting is "action allowed"
         */
        bool sheetProtected()     const;
        bool objectsProtected()   const;
        bool scenariosProtected() const;

        /**
         * @brief getter functions for detailed sheet protections
         * @note none of the sheet protection settings have any effect if protectSheet is not set
         */
        bool insertColumnsAllowed()       const;
        bool insertRowsAllowed()          const;
        bool deleteColumnsAllowed()       const;
        bool deleteRowsAllowed()          const;
        bool selectLockedCellsAllowed()   const;
        bool selectUnlockedCellsAllowed() const;

        /**
         * @brief get sheet password hash
         */
        std::string passwordHash() const;
        /**
         * @brief check sheet password protection
         */
        bool passwordIsSet() const;

        /**
         * @brief assemble a string summary about the sheet protection settings
         */
        std::string sheetProtectionSummary() const;

        /**
         * @brief test whether a worksheet relationships XML file exists for this worksheet
         */
        bool hasRelationships() const;

        /**
         * @brief test whether a VML drawing XML file exists for this worksheet
         */
        bool hasVmlDrawing() const;

        /**
         * @brief test whether a comments XML file exists for this worksheet
         */
        bool hasComments() const;

        /**
         * @brief test whether a tables XML file exists for this worksheet
         */
        bool hasTables() const;

        /**
         * @brief fetch a reference to the worksheet VML drawing object
         */
        XLVmlDrawing& vmlDrawing();

        /**
         * @brief fetch a reference to the worksheet comments
         */
        XLComments& comments();

        /**
         * @brief fetch a reference to the worksheet tables
         */
        XLTables& tables();

    private:

        /**
         * @brief fetch the # number from the xml path xl/worksheets/sheet#.xml
         */
        uint16_t sheetXmlNumber() const;

        /**
         * @brief fetch a reference to the worksheet relationships
         * @note private because transparent to the user
         */
        XLRelationships& relationships();

        /**
         * @brief
         * @return
         */
        XLColor getColor_impl() const;

        /**
         * @brief
         * @param color
         */
        void setColor_impl(const XLColor& color);

        /**
         * @brief
         * @return
         */
        bool isSelected_impl() const;

        /**
         * @brief
         * @param selected
         */
        void setSelected_impl(bool selected);

        /**
         * @brief
         * @return
         */
        bool isActive_impl() const;

        /**
         * @brief
         */
        bool setActive_impl();

    private:   // ---------- Private Member Variables ---------- //
        XLRelationships m_relationships{};    /**< class handling the worksheet relationships */
        XLMergeCells    m_merges{};           /**< class handling the <mergeCells> */
        XLVmlDrawing    m_vmlDrawing{};       /**< class handling the worksheet VML drawing object */
        XLComments      m_comments{};         /**< class handling the worksheet comments */
        XLTables        m_tables{};           /**< class handling the worksheet table settings */
        const std::vector< std::string_view >& m_nodeOrder = XLWorksheetNodeOrder;  // worksheet XML root node required child sequence
    };

    /**
     * @brief Class representing the an Excel chartsheet.
     * @todo This class is largely unimplemented and works just as a placeholder.
     */
    class OPENXLSX_EXPORT XLChartsheet final : public XLSheetBase<XLChartsheet>
    {
        friend class XLSheetBase<XLChartsheet>;

        //----------------------------------------------------------------------------------------------------------------------
        //           Public Member Functions
        //----------------------------------------------------------------------------------------------------------------------

    public:
        /**
         * @brief Default constructor
         */
        XLChartsheet() : XLSheetBase(nullptr) {};

        /**
         * @brief
         * @param xmlData
         */
        explicit XLChartsheet(XLXmlData* xmlData);

        /**
         * @brief
         * @param other
         */
        XLChartsheet(const XLChartsheet& other) = default;

        /**
         * @brief
         * @param other
         */
        XLChartsheet(XLChartsheet&& other) noexcept = default;

        /**
         * @brief
         */
        ~XLChartsheet();

        /**
         * @brief
         * @return
         */
        XLChartsheet& operator=(const XLChartsheet& other) = default;

        /**
         * @brief
         * @param other
         * @return
         */
        XLChartsheet& operator=(XLChartsheet&& other) noexcept = default;

    private:

        /**
         * @brief
         * @return
         */
        XLColor getColor_impl() const;

        /**
         * @brief
         * @param color
         */
        void setColor_impl(const XLColor& color);

        /**
         * @brief
         * @return
         */
        bool isSelected_impl() const;

        /**
         * @brief
         * @param selected
         */
        void setSelected_impl(bool selected);

        /**
         * @brief test issue #316 resolution
         */
        bool isActive_impl() const { return false; } // TODO: implement actual function body, if possible for chartsheets

        /**
         * @brief test issue #316 resolution
         */
        bool setActive_impl() { return true; } // TODO: implement actual function body, if possible for chartsheets

    private:   // ---------- Private Member Variables ---------- //
    };

    /**
     * @brief The XLAbstractSheet is a generalized sheet class, which functions as superclass for specialized classes,
     * such as XLWorksheet. It implements functionality common to all sheet types. This is a pure abstract class,
     * so it cannot be instantiated.
     */
    class OPENXLSX_EXPORT XLSheet final : public XLXmlFile
    {
    public:
        /**
         * @brief The constructor. There are no default constructor, so all parameters must be provided for
         * constructing an XLAbstractSheet object. Since this is a pure abstract class, instantiation is only
         * possible via one of the derived classes.
         * @param xmlData
         */
        explicit XLSheet(XLXmlData* xmlData);

        /**
         * @brief The copy constructor.
         * @param other The object to be copied.
         * @note The default copy constructor is used, i.e. only shallow copying of pointer data members.
         */
        XLSheet(const XLSheet& other) = default;

        /**
         * @brief
         * @param other
         */
        XLSheet(XLSheet&& other) noexcept = default;

        /**
         * @brief The destructor
         * @note The default destructor is used, since cleanup of pointer data members is not required.
         */
        ~XLSheet() = default;

        /**
         * @brief Assignment operator
         * @return A reference to the new object.
         * @note The default assignment operator is used, i.e. only shallow copying of pointer data members.
         */
        XLSheet& operator=(const XLSheet& other) = default;

        /**
         * @brief
         * @param other
         * @return
         */
        XLSheet& operator=(XLSheet&& other) noexcept = default;

        /**
         * @brief Method for getting the current visibility state of the sheet.
         * @return An XLSheetState enum object, with the current sheet state.
         */
        XLSheetState visibility() const;

        /**
         * @brief Method for setting the state of the sheet.
         * @param state An XLSheetState enum object with the new state.
         * @bug For some reason, this method doesn't work. The data is written correctly to the xml file, but the sheet
         * is not hidden when opening the file in Excel.
         */
        void setVisibility(XLSheetState state);

        /**
         * @brief
         * @return
         */
        XLColor color() const;

        /**
         * @brief
         * @param color
         */
        void setColor(const XLColor& color);

        /**
         * @brief Method for getting the index of the sheet.
         * @return An int with the index of the sheet.
         */
        uint16_t index() const;

        /**
         * @brief Method for setting the index of the sheet. This effectively moves the sheet to a different position.
         */
        void setIndex(uint16_t index);

        /**
         * @brief Method to retrieve the name of the sheet.
         * @return A std::string with the sheet name.
         */
        std::string name() const;

        /**
         * @brief Method for renaming the sheet.
         * @param name A std::string with the new name.
         */
        void setName(const std::string& name);

        /**
         * @brief Determine whether the sheet is selected
         * @return
         */
        bool isSelected() const;

        /**
         * @brief
         * @param selected
         */
        void setSelected(bool selected);

        /**
         * @brief
         * @return
         */
        bool isActive() const;

        /**
         * @brief
         */
        bool setActive();

        /**
         * @brief Method to get the type of the sheet.
         * @return An XLSheetType enum object with the sheet type.
         */
        template<
            typename SheetType,
                 typename = std::enable_if_t<std::is_same_v<SheetType, XLWorksheet> || std::is_same_v<SheetType, XLChartsheet>>>
        bool isType() const
        {
            return std::holds_alternative<SheetType>(m_sheet);
        }

        /**
         * @brief Method for cloning the sheet.
         * @param newName A std::string with the name of the clone
         * @return A pointer to the cloned object.
         * @note This is a pure abstract method. I.e. it is implemented in subclasses.
         */
        void clone(const std::string& newName);

        /**
         * @brief
         * @tparam T
         * @return
         */
        template<typename T, typename = std::enable_if_t<std::is_same_v<T, XLWorksheet> || std::is_same_v<T, XLChartsheet>>>
        T get() const
        {
            try {
                if constexpr (std::is_same<T, XLWorksheet>::value)
                    return std::get<XLWorksheet>(m_sheet);

                else if constexpr (std::is_same<T, XLChartsheet>::value)
                    return std::get<XLChartsheet>(m_sheet);
            }

            catch (const std::bad_variant_access&) {
                throw XLSheetError("XLSheet object does not contain the requested sheet type.");
            }
        }

        /**
         * @brief
         * @return
         */
        operator XLWorksheet() const;    // NOLINT

        /**
         * @brief
         * @return
         */
        operator XLChartsheet() const;    // NOLINT

        /**
         * @brief Print the XML contents of the XLSheet using the underlying XMLNode print function
         */
        void print(std::basic_ostream<char>& ostr) const;

    private:   // ---------- Private Member Variables ---------- //
        std::variant<XLWorksheet, XLChartsheet> m_sheet; /**<  */
    };
}    // namespace OpenXLSX

#ifdef _MSC_VER    // conditionally enable MSVC specific pragmas to avoid other compilers warning about unknown pragmas
#   pragma warning(pop)
#endif // _MSC_VER

#endif    // OPENXLSX_XLSHEET_HPP
