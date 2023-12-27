project(SudokuLib)

set(SOURCE_FILES MainFrame.cpp MainFrame.h
        ItemContainer.cpp
        ItemContainer.h
        Declaration.cpp
        Declaration.h
        ItemDigitMovable.cpp
        ItemDigitMovable.h
        ItemDigit.h
        ItemDigit.cpp
        Item.cpp
        Item.h
        Level.cpp
        Level.h
        ItemSparty.cpp
        ItemSparty.h
        Sudoku.cpp
        Sudoku.h
        SudokuView.cpp
        SudokuView.h
        Visitor.h
        ItemXRay.cpp
        ItemXRay.h
        pch.h
        ids.h
        ItemBackground.cpp
        ItemBackground.h
        DeclarationBackground.cpp
        DeclarationBackground.h
        DeclarationContainer.cpp
        DeclarationContainer.h
        DeclarationDigit.cpp
        DeclarationDigit.h
        DeclarationSparty.cpp
        DeclarationSparty.h
        DeclarationXRay.cpp
        DeclarationXRay.h
        ScoreBoard.cpp
        ScoreBoard.h
        Popup.cpp
        Popup.h
        SudokuVisitor.cpp
        SudokuVisitor.h
        SpartyVisitor.cpp
        SpartyVisitor.h
        ContainerVisitor.cpp
        ContainerVisitor.h
        ItemDigitVisitor.cpp
        ItemDigitVisitor.h
        EatVisitor.cpp
        EatVisitor.h
        RegurgitateVisitor.cpp
        RegurgitateVisitor.h
        DeclarationEnemy.cpp
        DeclarationEnemy.h
        ItemEnemy.cpp
        ItemEnemy.h
        XRayVisitor.cpp
        XRayVisitor.h
        SolveVisitor.cpp
        SolveVisitor.h
        ItemDigitGiven.h
        ItemDigitGiven.cpp
        PopupManager.cpp
        PopupManager.h
        PopupInstructions.cpp
        PopupInstructions.h
        PopupFull.cpp
        PopupFull.h
        PopupCollision.cpp
        PopupCollision.h
        PopupWinLoss.cpp
        PopupWinLoss.h
        DigitResetVisitor.cpp
        DigitResetVisitor.h
        PopupCaught.cpp
        PopupCaught.h
)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)