Attribute VB_Name = "swConst"
' SolidWorks constants from ./samples/appcomm/swconst.bas file
'
' ----
'  Document Types
' ----

Public Enum swFileLoadError_e
    swGenericError = 1
    swFileNotFoundError = 2
    swIdMatchError = 4
    swReadOnlyWarn = 8
    swSharingViolationWarn = 16
End Enum

Public Enum swDocumentTypes_e
    swDocNONE = 0
    swDocPART = 1
    swDocASSEMBLY = 2
    swDocDRAWING = 3
End Enum

' ----
'  Selection Types
' ----

'  The following are the possible type ids returned by the function
'      ISelectionMgr::GetSelectedObjectType.
'  The string names to the right of the type id definition is the "type name"
'      used by the methods:  IModelDoc::SelectByID && AndSelectByID

Public Enum swSelectType_e
    swSelNOTHING = 0

    swSelEDGES = 1
    swSelFACES = 2
    swSelVERTICES = 3

    swSelDATUMPLANES = 4
    swSelDATUMAXES = 5
    swSelDATUMPOINTS = 6

    swSelOLEITEMS = 7

    swSelATTRIBUTES = 8

    swSelSKETCHES = 9

    swSelSKETCHSEGS = 10
    swSelSKETCHPOINTS = 11

    swSelDRAWINGVIEWS = 12

    swSelGTOLS = 13
    swSelDIMENSIONS = 14
    swSelNOTES = 15
    swSelSECTIONLINES = 16
    swSelDETAILCIRCLES = 17
    swSelSECTIONTEXT = 18
    swSelSHEETS = 19

    swSelCOMPONENTS = 20
    swSelMATES = 21

    swSelBODYFEATURES = 22

    swSelREFCURVES = 23

    swSelEXTSKETCHSEGS = 24
    swSelEXTSKETCHPOINTS = 25

    swSelHELIX = 26
    swSelREFSURFACES = 27

    swSelCENTERMARKS = 28
    swSelINCONTEXTFEAT = 29
    swSelMATEGROUP = 30

    'swSelEVERYTHING = 4294967293#
    'swSelUNSUPPORTED = 4294967295#
End Enum

' ----
'  Events Notifications
' ----

Public Enum swViewNotify_e
    swViewRepaintNotify = 1
    swViewChangeNotify = 2
    swViewDestroyNotify = 3
    swViewRepaintPostNotify = 4
End Enum

Public Enum swFMViewNotify_e
    swFMViewActivateNotify = 1
    swFMViewDeactivateNotify = 2
    swFMViewDestroyNotify = 3
End Enum

Public Enum swPartNotify_e
    swPartRegenNotify = 1
    swPartDestroyNotify = 2
    swPartRegenPostNotify = 3
    swPartViewNewNotify = 4
    swPartNewSelectionNotify = 5
    swPartFileSaveNotify = 6
    swPartFileSaveAsNotify = 7
    swPartLoadFromStorageNotify = 8
    swPartSaveToStorageNotify = 9
    swPartConfigChangeNotify = 10
    swPartConfigChangePostNotify = 11
End Enum

Public Enum swDrawingNotify_e
    swDrawingRegenNotify = 1
    swDrawingDestroyNotify = 2
    swDrawingRegenPostNotify = 3
    swDrawingViewNewNotify = 4
    swDrawingNewSelectionNotify = 5
    swDrawingFileSaveNotify = 6
    swDrawingFileSaveAsNotify = 7
    swDrawingLoadFromStorageNotify = 8
    swDrawingSaveToStorageNotify = 9
End Enum

Public Enum swAssemblyNotify_e
    swAssemblyRegenNotify = 1
    swAssemblyDestroyNotify = 2
    swAssemblyRegenPostNotify = 3
    swAssemblyViewNewNotify = 4
    swAssemblyNewSelectionNotify = 5
    swAssemblyFileSaveNotify = 6
    swAssemblyFileSaveAsNotify = 7
    swAssemblyLoadFromStorageNotify = 8
    swAssemblySaveToStorageNotify = 9
    swAssemblyConfigChangeNotify = 10
    swAssemblyConfigChangePostNotify = 11
End Enum

Public Enum swAppNotify_e
    swAppFileOpenNotify = 1
    swAppFileNewNotify = 2
    swAppDestroyNotify = 3
    swAppActiveDocChangeNotify = 4
    swAppActiveModelDocChangeNotify = 5
End Enum


' ----
'  Parameter Types
' ----
Public Enum swParamType_e
    swParamTypeDouble = 0
    swParamTypeString = 1
    swParamTypeInteger = 2
    swParamTypeDVector = 3
End Enum

' ----
'  The following is for angular dimension info returned GetDimensionInfo()
' ----
Public Enum swQuadant_e
    swQuadUnknown = 0
    swQuadPosQ1 = 1
    swQuadNegQ1 = 2
    swQuadPosQ2 = 3
    swQuadNegQ2 = 4
End Enum

' ----
'  The following enum is for interpreting ellipse data
' ----
Public Enum swEllipsePts_e
    swEllipseStartPt = 0
    swEllipseEndPt = 1
    swEllipseCenterPt = 2
    swEllipseMajorPt = 3
    swEllipseMinorPt = 4
End Enum

' ----
'  The following define gtol symbol indices
' ----
Public Enum swGtolMatCondition_e
    swMcNONE = 0
    swMcMMC = 1
    swMcRFS = 2
    swMcLMC = 3
End Enum

Public Enum swGtolModifyingSymbol_e
    swMsNONE = 4
    swMsPROJTOLZONE = 5
    swMsDIA = 6
    swMsSPHDIA = 7
    swMsRAD = 8
    swMsSPHRAD = 9
    swMsREF = 10
    swMsARCLEN = 11
End Enum

Public Enum swGtolGeomCharSymbol_e
    swGcsNONE = 12
    swGcsSYMMETRY = 13
    swGcsSTRAIGHT = 14
    swGcsFLAT = 15
    swGcsROUND = 16
    swGcsCYL = 17
    swGcsLINEPROF = 18
    swGcsSURFPROF = 19
    swGcsANG = 20
    swGcsPERP = 21
    swGcsPARALLEL = 22
    swGcsPOSITION = 23
    swGcsCONC = 24
    swGcsCIRCRUNOUT = 25
    swGcsTOTALRUNOUT = 26
End Enum

' ----
'  Assembly Mate Information
' ----
Public Enum swMateType_e
    swMateCOINCIDENT = 0
    swMateCONCENTRIC = 1
    swMatePERPENDICULAR = 2
    swMatePARALLEL = 3
    swMateTANGENT = 4
    swMateDISTANCE = 5
    swMateANGLE = 6
End Enum

Public Enum swMateAlign_e
    swAlignNONE = 0
    swAlignSAME = 1
    swAlignAGAINST = 2
End Enum


Public Enum swDisplayMode_e
    swWIREFRAME = 0
    swHIDDEN_GREYED = 1
    swHIDDEN = 2
End Enum

' ----
'  Arrow Information
' ----
Public Enum swArrowStyle_e
    swOPEN_ARROWHEAD = 0
    swCLOSED_ARROWHEAD = 1
    swSLASH_ARROWHEAD = 2
    swDOT_ARROWHEAD = 3
    swORIGIN_ARROWHEAD = 4
    swWIDE_ARROWHEAD = 5
    swNO_ARROWHEAD = 6
End Enum


Public Enum swLeaderSide_e
    swLS_SMART = 0
    swLS_LEFT = 1
    swLS_RIGHT = 2
End Enum


' ----
'  The following define Surface Finish Symbol types and options
'  Used by InsertSurfaceFinishSymbol, ModifySurfaceFinishSymbol
' ----
Public Enum swSFSymType_e
    swSFBasic = 0
    swSFMachining_Req = 1
    swSFDont_Machine = 2
End Enum

Public Enum swSFLaySym_e
    swSFNone = 0
    swSFCircular = 1
    swSFCross = 2
    swSFMultiDir = 3
    swSFParallel = 4
    swSFPerp = 5
    swSFRadial = 6
    swSFParticulate = 7
End Enum

Public Enum swLeaderStyle_e
    swNO_LEADER = 0
    swSTRAIGHT = 1
    swBENT = 2
End Enum

' ----
'  Balloon Information.  swBS_SplitCirc is not valid for Notes only for Balloons
' ----
Public Enum swBalloonStyle_e
    swBS_None = 0
    swBS_Circular = 1
    swBS_Triangle = 2
    swBS_Hexagon = 3
    swBS_Box = 4
    swBS_Diamond = 5
    swBS_SplitCirc = 6
End Enum

Public Enum swBalloonFit_e
    swBF_Tightest = 0
    swBF_1Char = 1
    swBF_2Chars = 2
    swBF_3Chars = 3
    swBF_4Chars = 4
    swBF_5Chars = 5
End Enum


' ----
'  The following define length and angle unit types
' ----
Public Enum swLengthUnit_e
    swMM = 0
    swCM = 1
    swMETER = 2
    swINCHES = 3
    swFEET = 4
    swFEETINCHES = 5
End Enum

Public Enum swAngleUnit_e
    swDEGREES = 0
    swDEG_MIN = 1
    swDEG_MIN_SEC = 2
    swRADIANS = 3
End Enum

Public Enum swFractionDisplay_e
    swNONE = 0
    swDECIMAL = 1
    swFRACTION = 2
End Enum

' ----
'  Drawing Paper Sizes
' ----
Public Enum swDwgPaperSizes_e
    swDwgPaperAsize = 0
    swDwgPaperAsizeVertical = 1
    swDwgPaperBsize = 2
    swDwgPaperCsize = 3
    swDwgPaperDsize = 4
    swDwgPaperEsize = 5
    swDwgPaperA4size = 6
    swDwgPaperA4sizeVertical = 7
    swDwgPaperA3size = 8
    swDwgPaperA2size = 9
    swDwgPaperA1size = 10
    swDwgPaperA0size = 11
    swDwgPapersUserDefined = 12
End Enum


' ----
'  Drawing Templates
' ----
Public Enum swDwgTemplates_e
    swDwgTemplateAsize = 0
    swDwgTemplateAsizeVertical = 1
    swDwgTemplateBsize = 2
    swDwgTemplateCsize = 3
    swDwgTemplateDsize = 4
    swDwgTemplateEsize = 5
    swDwgTemplateA4size = 6
    swDwgTemplateA4sizeVertical = 7
    swDwgTemplateA3size = 8
    swDwgTemplateA2size = 9
    swDwgTemplateA1size = 10
    swDwgTemplateA0size = 11
    swDwgTemplateCustom = 12
    swDwgTemplateNone = 13
End Enum

' ----
'  Drawing Templates
' ----
Public Enum swStandardViews_e
    swFrontView = 1
    swBackView = 2
    swLeftView = 3
    swRightView = 4
    swTopView = 5
    swBottomView = 6
    swIsometricView = 7
    swTrimetricView = 8
    swDimetricView = 9
End Enum

' ----
'  Repaint Notification types
' ----
Public Enum swRepaintTypes_e
    swStandardUpdate = 0
    swLightUpdate = 1
    swMaterialUpdate = 2
    swSectionedUpdate = 3
    swExplodedUpdate = 4
    swInsertSketchUpdate = 5
End Enum

' ----
'  User Interface State
' ----
Public Enum swUIStates_e
    swIsHiddenInFeatureMgr = 1
End Enum

' ----
'  Type names
' ----

'  Body Features
Public Const swTnChamfer As String = "Chamfer"
Public Const swTnFillet As String = "Fillet"
Public Const swTnCavity As String = "Cavity"
Public Const swTnDraft As String = "Draft"
Public Const swTnMirrorSolid As String = "MirrorSolid"
Public Const swTnCirPattern As String = "CirPattern"
Public Const swTnLPattern As String = "LPattern"
Public Const swTnMirrorPattern As String = "MirrorPattern"
Public Const swTnShell As String = "Shell"
Public Const swTnBlend As String = "Blend"
Public Const swTnBlendCut As String = "BlendCut"
Public Const swTnExtrusion As String = "Extrusion"
Public Const swTnBoss As String = "Boss"
Public Const swTnCut As String = "Cut"
Public Const swTnRefCurve As String = "RefCurve"
Public Const swTnRevolution As String = "Revolution"
Public Const swTnRevCut As String = "RevCut"
Public Const swTnSweep As String = "Sweep"
Public Const swTnSweepCut As String = "SweepCut"
Public Const swTnStock As String = "Stock"
Public Const swTnSurfCut As String = "SurfCut"
Public Const swTnThicken As String = "Thicken"
Public Const swTnThickenCut As String = "ThickenCut"
Public Const swTnVarFillet As String = "VarFillet"
Public Const swTnSketchHole As String = "SketchHole"
Public Const swTnHoleWzd As String = "HoleWzd"
Public Const swTnImported As String = "Imported"
Public Const swTnBaseBody As String = "BaseBody"

'  Drawing Related
Public Const swTnCenterMark As String = "CenterMark"
Public Const swTnDrSheet As String = "DrSheet"
Public Const swTnAbsoluteView As String = "AbsoluteView"
Public Const swTnDetailView As String = "DetailView"
Public Const swTnRelativeView As String = "RelativeView"
Public Const swTnSectionPartView As String = "SectionPartView"
Public Const swTnSectionAssemView As String = "SectionAssemView"
Public Const swTnUnfoldedView As String = "UnfoldedView"
Public Const swTnAuxiliaryView As String = "AuxiliaryView"
Public Const swTnDetailCircle As String = "DetailCircle"
Public Const swTnDrSectionLine As String = "DrSectionLine"

'  Assembly Related
Public Const swTnMateCoincident As String = "MateCoincident"
Public Const swTnMateConcentric As String = "MateConcentric"
Public Const swTnMateDistanceDim As String = "MateDistanceDim"
Public Const swTnMateParallel As String = "MateParallel"
Public Const swTnMateTangent As String = "MateTangent"
Public Const swTnReference As String = "Reference"

'  Reference Geometry
Public Const swTnRefPlane As String = "RefPlane"
Public Const swTnRefAxis As String = "RefAxis"
Public Const swTnReferenceCurve As String = "ReferenceCurve"
Public Const swTnRefSurface As String = "RefSurface"

'  Misc
Public Const swTnAttribute As String = "Attribute"
Public Const swTnProfileFeature As String = "ProfileFeature"

'  Symbol markers
Public Const SYMBOL_MARKER_START As String = "<"
Public Const SYMBOL_MARKER_END As String = ">"
Public Const SYMBOL_MARKER_SPACE As String = "-"


' ----
'  Surface Types.  For use with Surface::Identity method.
' ----
Public Const PLANE_TYPE As Integer = 4001
Public Const CYLINDER_TYPE As Integer = 4002
Public Const CONE_TYPE As Integer = 4003
Public Const SPHERE_TYPE As Integer = 4004
Public Const TORUS_TYPE As Integer = 4005
Public Const BSURF_TYPE As Integer = 4006
Public Const BLEND_TYPE As Integer = 4007
Public Const OFFSET_TYPE As Integer = 4008
Public Const EXTRU_TYPE As Integer = 4009
Public Const SREV_TYPE As Integer = 4010

' ----
'  Curve Types.  For use with Curve::Identity method.
' ----
Public Const LINE_TYPE As Integer = 3001
Public Const CIRCLE_TYPE As Integer = 3002
Public Const ELLIPSE_TYPE As Integer = 3003
Public Const INTERSECTION_TYPE As Integer = 3004
Public Const BCURVE_TYPE As Integer = 3005
Public Const SPCURVE_TYPE As Integer = 3006
Public Const CONSTPARAM_TYPE As Integer = 3008
Public Const TRIMMED_TYPE As Integer = 3009



'  Items that can be configured to have a line style in drawings.
Public Enum swLineTypes_e
    swLF_VISIBLE = 0
    swLF_HIDDEN = 1
    swLF_SKETCH = 2
    swLF_DETAIL = 3
    swLF_SECTION = 4
    swLF_DIMENSION = 5
    swLF_CENTER = 6
    swLF_HATCH = 7
    swLF_TANGENT = 8
End Enum

'  Dimension tolerance types
Public Enum swTolType_e
    swTolNONE = 0
    swTolBASIC = 1
    swTolBILAT = 2
    swTolLIMIT = 3
    swTolSYMMETRIC = 4
    swTolMIN = 5
    swTolMAX = 6
    swTolMETRIC = 7
End Enum

'  Tolerances which the user can set using Modeler::SetTolerances
Public Enum swTolerances_e
    swBSCurveOutputTol = 0
    swBSCurveNonRationalOutputTol = 1
    swUVCurveOutputTol = 2
End Enum

' ----
'  Mate Entity Types
'
'   The following are the possible mate entity type ids returned by the function
'   IMateEntity::GetEntityType.
' ----
Public Enum swMateEntityTypes_e
    swMateUnsupported = 0
    swMatePoint = 1
    swMateLine = 2
    swMatePlane = 3
    swMateCylinder = 4
    swMateCone = 5
End Enum

' ----
'  Attribute Callback Support
'
'   The following are the possible callback types for IAttributeDefs
' ----
Public Enum swAttributeCallbackTypes_e
    swACBDelete = 0
End Enum

Public Enum swAttributeCallbackOptions_e
    swACBRequiresCallback = 1
End Enum

Public Enum swAttributeCallbackReturnValues_e
    swACBDeleteIt = 1
End Enum

'  Text reference point position
Public Enum swTextPosition_e
    swUPPER_LEFT = 0
    swLOWER_LEFT = 1
    swCENTER = 2
End Enum

' ----
'  The following are the different types of topology resulting from a call to GetTrimCurves
' ----
Public Enum swTopologyTypes_e
    swTopologyNull = 0
    swTopologyCoEdge = 1
    swTopologyVertex = 2
End Enum


' ----
'  Attributes associated entity state
' ----
Public Enum swAssociatedEntityStates_e
    swIsEntityInvalid = 0
    swIsEntitySuppressed = 1
    swIsEntityAmbiguous = 2

End Enum

' ---
'  Search Folder Types
' ---
Public Enum swSearchFolderTypes_e
    swDocumentType = 0
End Enum


' ---
'  User Preference Toggles.
'  The different User Preference Toggles for GetUserPreferenceToggle & SetUserPreferenceToggle
' ---
Public Enum swUserPreferenceToggle_e
    swUseFolderSearchRules = 0
    swDisplayArcCenterPoints = 1
    swDisplayEntityPoints = 2
    swIgnoreFeatureColors = 3
    swDisplayAxes = 4
    swDisplayPlanes = 5
    swDisplayOrigins = 6
    swDisplayTemporaryAxes = 7
End Enum

' ---
'  User Preference Double Values
'  The different User Preference Double Values for GetUserPreferenceDoubleValue & SetUserPreferenceDoubleValue
' ---
Public Enum swUserPreferenceDoubleValue_e
    swDetailingNoteFontHeight = 0
    swDetailingDimFontHeight = 1
    swSTLDeviation = 2
    swSTLAngleTolerance = 3
    swSpinBoxMetricLengthIncrement = 4
    swSpinBoxEnglishLengthIncrement = 5
    swSpinBoxAngleIncrement = 6
    swMaterialPropertyDensity = 7
End Enum

' ---
'  View Display States
'  The different View Display States for IModelView::GetDisplayState
' ---
Public Enum swViewDisplayType_e
    swIsViewSectioned = 0
    swIsViewPerspective = 1
    swIsViewShaded = 2
    swIsViewWireFrame = 3
    swIsViewHiddenLinesRemoved = 4
    swIsViewHiddenInGrey = 5
    swIsViewCurvature = 6
End Enum

' ----
'  Control display of internal sketch points
' ----
Public Enum swSkInternalPntOpts_e
    swSkPntsOff = 0
    swSkPntsOn = 1
    swSkPntsDefault = 2
End Enum

' ----
'  DXF/DWG Output formats
' ----
Public Enum swDxfFormat_e
    swDxfFormat_R12 = 0
    swDxfFormat_R13 = 1
    swDxfFormat_R14 = 2
End Enum


' ---
'  User Preference Double Values
'  The different User Preference Integer Values for GetUserPreferenceIntegerValue & SetUserPreferenceDoubleValue
' ---
Public Enum swUserPreferenceIntegerValue_e
    swDxfVersion = 0
    swDxfOutputFonts = 1
End Enum


' ---
'  DXF/DWG output arrow directions
' ---
Public Enum swArrowDirection_e
    swINSIDE = 0
    swOUTSIDE = 1
    swSMART = 2
End Enum


' ---
'  Print Properties
'  The different property types for IModelDoc::SetPrintSetUp
' ---
Public Enum swPrintProperties_e
    swPrintPaperSize = 0
    swPrintOrientation = 1
End Enum

' ----
'  Body operations.  For use with Body::Operations method.
' ----
Public Const SWBODYINTERSECT As Integer = 15901
Public Const SWBODYCUT As Integer = 15902
Public Const SWBODYADD As Integer = 15903

' ---
'  End Conditions.
'  These are used with FeatureBoss, FeatureCut, FeatureExtrusion, etc.
'  Not all types are valid for all body operations.  Some of these end conditions require additional
'  selections (ie - swEndCondUpToSurface, etc.) and some require additional data (ie - swEndCondOffsetFromSurface)
' ---
Public Enum swEndConditions_e
    swEndCondBlind = 0
    swEndCondThroughAll = 1
    swEndCondThroughNext = 2
    swEndCondUpToVertex = 3
    swEndCondUpToSurface = 4
    swEndCondOffsetFromSurface = 5
    swEndCondMidPlane = 6
End Enum

