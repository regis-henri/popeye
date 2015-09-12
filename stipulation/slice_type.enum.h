typedef enum
{
 STProxy, STTemporaryHackFork, STStipulationCompleter, STCountersWriter, STStartOfStipulationSpecific, STStipulationCopier, STProofSolverBuilder, STAToBSolverBuilder, STEndOfStipulationSpecific, STSolvingMachineryIntroBuilder, STStartOfWriterBuilders, STOutputPlainTextOptionNoboard, STOutputPlainTextPositionWriterBuilder, STOutputPlainTextProofPositionWriterBuilder, STOutputPlainTextAToBStartPositionWriterBuilder, STOutputPlainTextConditionsWriterBuilder, STOutputPlainTextQuodlibetWriterBuilder, STOutputPlainTextMutuallyExclusiveCastlingsWriterBuilder, STOutputPlainTextDuplexWriterBuilder, STOutputPlainTextHalfDuplexWriterBuilder, STOutputPlainTextSeparateGridWriterBuilder, STOutputLaTeXPositionWriterBuilder, STOutputLaTeXTwinningWriterBuilder, STTwinIdAdjuster, STConditionsResetter, STOptionsResetter, STCommandLineOptionsParser, STInputPlainTextOpener, STPlatformInitialiser, STHashTableDimensioner, STTimerStarter, STZeroPositionInitialiser, STZeropositionSolvingStopper, STCheckDirInitialiser, STOutputLaTeXCloser, STOutputPlainTextVersionInfoPrinter, STInputPlainTextUserLanguageDetector, STInputPlainTextProblemsIterator, STInputPlainTextProblemHandler, STInputPlainTextInitialTwinReader, STInputPlainTextTwinsHandler, STStartOfCurrentTwin, STDuplexSolver, STHalfDuplexSolver, STCreateBuilderSetupPly, STPieceWalkCacheInitialiser, STPiecesCounter, STPiecesFlagsInitialiser, STRoyalsLocator, STProofgameVerifyUniqueGoal, STProofgameInitialiser, STAToBInitialiser, STInputVerification, STMoveEffectsJournalReset, STSolversBuilder, STProxyResolver, STSlackLengthAdjuster, STStartOfStipulation, STAttackAdapter, STDefenseAdapter, STReadyForAttack, STReadyForDefense, STNotEndOfBranchGoal, STNotEndOfBranch, STMinLengthOptimiser, STHelpAdapter, STReadyForHelpMove, STSetplayFork, STRetroStartRetractionPly, STRetroRetractLastCapture, STRetroUndoLastPawnMultistep, STRetroStartRetroMovePly, STRetroPlayNullMove, STRetroRedoLastCapture, STRetroRedoLastPawnMultistep, STEndOfBranch, STEndOfBranchForced, STEndOfBranchGoal, STEndOfBranchTester, STEndOfBranchGoalTester, STAvoidUnsolvable, STResetUnsolvable, STLearnUnsolvable, STConstraintSolver, STConstraintTester, STGoalConstraintTester, STEndOfRoot, STEndOfIntro, STDeadEnd, STMove, STForEachAttack, STForEachDefense, STFindAttack, STFindDefense, STPostMoveIterationInitialiser, STMoveGenerationPostMoveIterator, STSquareObservationPostMoveIterator, STMoveEffectJournalUndoer, STMovePlayer, STCastlingPlayer, STEnPassantAdjuster, STPawnPromoter, STFootballChessSubsitutor, STBeforePawnPromotion, STLandingAfterPawnPromotion, STNullMovePlayer, STLandingAfterMovingPieceMovement, STLandingAfterMovePlay, STAttackPlayed, STDefensePlayed, STHelpMovePlayed, STDummyMove, STShortSolutionsStart, STIfThenElse, STCheckZigzagLanding, STBlackChecks, STSingleBoxType1LegalityTester, STSingleBoxType2LegalityTester, STSingleBoxType3PawnPromoter, STSingleBoxType3TMovesForPieceGenerator, STSingleBoxType3LegalityTester, STSingleBoxType3EnforceObserverWalk, STIsardamLegalityTester, STCirceAssassinAssassinate, STCirceAssassinAllPieceObservationTester, STCirceParachuteRemember, STCirceVolcanicRemember, STCirceVolcanicSwapper, STCirceParachuteUncoverer, STKingSquareUpdater, STOwnKingCaptureAvoider, STOpponentKingCaptureAvoider, STPatienceChessLegalityTester, STGoalReachedTester, STGoalMateReachedTester, STGoalStalemateReachedTester, STGoalDoubleStalemateReachedTester, STGoalTargetReachedTester, STGoalCheckReachedTester, STGoalCaptureReachedTester, STGoalSteingewinnReachedTester, STGoalEnpassantReachedTester, STGoalDoubleMateReachedTester, STGoalCounterMateReachedTester, STGoalCastlingReachedTester, STGoalAutoStalemateReachedTester, STGoalCircuitReachedTester, STGoalExchangeReachedTester, STGoalCircuitByRebirthReachedTester, STGoalExchangeByRebirthReachedTester, STGoalAnyReachedTester, STGoalProofgameReachedTester, STGoalAToBReachedTester, STGoalMateOrStalemateReachedTester, STGoalChess81ReachedTester, STGoalKissReachedTester, STGoalImmobileReachedTester, STGoalNotCheckReachedTester, STGoalKingCaptureReachedTester, STTrue, STFalse, STAnd, STOr, STNot, STSelfCheckGuard, STOhneschachStopIfCheck, STOhneschachStopIfCheckAndNotMate, STOhneschachDetectUndecidableGoal, STRecursionStopper, STMoveInverter, STMoveInverterSetPlay, STMinLengthGuard, STForkOnRemaining, STFindShortest, STFindByIncreasingLength, STGeneratingMoves, STExecutingKingCapture, STDoneGeneratingMoves, STDoneRemovingIllegalMoves, STDoneRemovingFutileMoves, STDonePriorisingMoves, STMoveGenerator, STKingMoveGenerator, STNonKingMoveGenerator, STCastlingIntermediateMoveLegalityTester, STCastlingRightsAdjuster, STMoveGeneratorFork, STGeneratingMovesForPiece, STGeneratedMovesForPiece, STMovesForPieceBasedOnWalkGenerator, STCastlingGenerator, STRefutationsAllocator, STRefutationsSolver, STRefutationsFilter, STEndOfRefutationSolvingBranch, STPlaySuppressor, STContinuationSolver, STSolvingContinuation, STThreatSolver, STThreatEnforcer, STThreatStart, STThreatEnd, STThreatCollector, STThreatDefeatedTester, STRefutationsCollector, STRefutationsAvoider, STLegalAttackCounter, STLegalDefenseCounter, STAnyMoveCounter, STCaptureCounter, STTestingPrerequisites, STDoubleMateFilter, STCounterMateFilter, STPrerequisiteOptimiser, STNoShortVariations, STRestartGuard, STRestartGuardNested, STRestartGuardIntelligent, STIntelligentTargetCounter, STMaxTimeSetter, STMaxTimeGuard, STMaxSolutionsResetter, STMaxSolutionsInitialiser, STMaxSolutionsGuard, STMaxSolutionsCounter, STEndOfBranchGoalImmobile, STDeadEndGoal, STOrthodoxMatingMoveGenerator, STOrthodoxMatingKingContactGenerator, STKillerAttackCollector, STKillerDefenseCollector, STKillerMovePrioriser, STKillerMoveFinalDefenseMove, STEnPassantFilter, STEnPassantRemoveNonReachers, STCastlingFilter, STCastlingRemoveNonReachers, STChess81RemoveNonReachers, STCaptureRemoveNonReachers, STTargetRemoveNonReachers, STDetectMoveRetracted, STRetractionPrioriser, STUncapturableRemoveCaptures, STNocaptureRemoveCaptures, STWoozlesRemoveIllegalCaptures, STBiWoozlesRemoveIllegalCaptures, STHeffalumpsRemoveIllegalCaptures, STBiHeffalumpsRemoveIllegalCaptures, STProvocateursRemoveUnobservedCaptures, STLortapRemoveSupportedCaptures, STPatrolRemoveUnsupportedCaptures, STUltraPatrolMovesForPieceGenerator, STBackhomeExistanceTester, STBackhomeRemoveIllegalMoves, STNoPromotionsRemovePromotionMoving, STGridRemoveIllegalMoves, STMonochromeRemoveBichromeMoves, STBichromeRemoveMonochromeMoves, STEdgeMoverRemoveIllegalMoves, STShieldedKingsRemoveIllegalCaptures, STSuperguardsRemoveIllegalCaptures, STKoekoLegalityTester, STGridContactLegalityTester, STAntiKoekoLegalityTester, STNewKoekoRememberContact, STNewKoekoLegalityTester, STJiggerLegalityTester, STTakeAndMakeGenerateMake, STTakeAndMakeAvoidPawnMakeToBaseLine, STWormholeRemoveIllegalCaptures, STWormholeTransferer, STHashOpener, STAttackHashed, STAttackHashedTester, STHelpHashed, STHelpHashedTester, STIntelligentMovesLeftInitialiser, STIntelligentMateFilter, STIntelligentStalemateFilter, STIntelligentProof, STGoalReachableGuardFilterMate, STGoalReachableGuardFilterStalemate, STGoalReachableGuardFilterProof, STGoalReachableGuardFilterProofFairy, STIntelligentSolutionsPerTargetPosResetter, STIntelligentSolutionsPerTargetPosCounter, STIntelligentLimitNrSolutionsPerTargetPos, STIntelligentDuplicateAvoider, STIntelligentSolutionRememberer, STIntelligentImmobilisationCounter, STKeepMatingFilter, STMaxFlightsquares, STFlightsquaresCounter, STDegenerateTree, STMaxNrNonTrivial, STMaxNrNonTrivialCounter, STMaxThreatLength, STMaxThreatLengthStart, STStopOnShortSolutionsResetter, STStopOnShortSolutionsInitialiser, STStopOnShortSolutionsFilter, STAmuMateFilter, STUltraschachzwangLegalityTester, STCirceSteingewinnFilter, STCirceCircuitSpecial, STCirceExchangeSpecial, STPiecesParalysingMateFilter, STPiecesParalysingMateFilterTester, STPiecesParalysingStalemateSpecial, STPiecesParalysingRemoveCaptures, STPiecesParalysingSuffocationFinderFork, STPiecesParalysingSuffocationFinder, STPiecesKamikazeTargetSquareFilter, STPiecesHalfNeutralRecolorer, STMadrasiMovesForPieceGenerator, STEiffelMovesForPieceGenerator, STDisparateMovesForPieceGenerator, STParalysingMovesForPieceGenerator, STParalysingObserverValidator, STParalysingObservationGeometryValidator, STCentralMovesForPieceGenerator, STCentralObservationValidator, STBeamtenMovesForPieceGenerator, STImmobilityTester, STOpponentMovesCounterFork, STOpponentMovesCounter, STOpponentMovesFewMovesPrioriser, STStrictSATInitialiser, STStrictSATUpdater, STDynastyKingSquareUpdater, STHurdleColourChanger, STHurdleColourChangeInitialiser, STHurdleColourChangerChangePromoteeInto, STOscillatingKingsTypeA, STOscillatingKingsTypeB, STOscillatingKingsTypeC, STPawnToImitatorPromoter, STExclusiveChessExclusivityDetector, STExclusiveChessNestedExclusivityDetector, STExclusiveChessLegalityTester, STExclusiveChessMatingMoveCounterFork, STExclusiveChessGoalReachingMoveCounter, STExclusiveChessUndecidableWriterTree, STExclusiveChessUndecidableWriterLine, STExclusiveChessGoalReachingMoveCounterSelfCheckGuard, STMaffImmobilityTesterKing, STOWUImmobilityTesterKing, STBrunnerDefenderFinder, STKingCaptureLegalityTester, STMoveLegalityTester, STCageCirceNonCapturingMoveFinder, STCageCirceFutileCapturesRemover, STSinglePieceMoveGenerator, STMummerOrchestrator, STMummerBookkeeper, STMummerDeadend, STUltraMummerMeasurerFork, STUltraMummerMeasurerDeadend, STBackHomeFinderFork, STBackHomeMovesOnly, STCheckTesterFork, STTestingCheck, STTestedCheck, STNoCheckConceptCheckTester, STVogtlaenderCheckTester, STExtinctionExtinctedTester, STExtinctionAllPieceObservationTester, STCastlingGeneratorTestDeparture, STNoKingCheckTester, STSATCheckTester, STSATxyCheckTester, STStrictSATCheckTester, STKingSquareObservationTesterPlyInitialiser, STAntikingsCheckTester, STKingCapturedObservationGuard, STKingSquareObservationTester, STBGLEnforcer, STBGLAdjuster, STMasandRecolorer, STMasandEnforceObserver, STMessignyMovePlayer, STActuatedRevolvingCentre, STActuatedRevolvingBoard, STRepublicanKingPlacer, STRepublicanType1DeadEnd, STCirceConsideringRebirth, STGenevaConsideringRebirth, STMarsCirceConsideringRebirth, STMarsCirceConsideringObserverRebirth, STAntimarsCirceConsideringRebirth, STGenevaStopCaptureFromRebirthSquare, STCirceCaptureFork, STCirceParrainThreatFork, STAprilCaptureFork, STCircePreventKingRebirth, STCirceInitialiseRelevantFromReborn, STCirceDeterminingRebirth, STCirceDeterminedRebirth, STCirceInitialiseFromCurrentMove, STCirceInitialiseFromLastMove, STCirceInitialiseRebornFromCapturee, STAntiCloneCirceDetermineRebornWalk, STCirceCloneDetermineRebornWalk, STCirceDoubleAgentsAdaptRebornSide, STChameleonCirceAdaptRebornWalk, STCirceEinsteinAdjustRebornWalk, STCirceReversalEinsteinAdjustRebornWalk, STCirceCouscousMakeCapturerRelevant, STAnticirceCouscousMakeCaptureeRelevant, STMirrorCirceOverrideRelevantSide, STCirceDetermineRebirthSquare, STCirceFrischaufAdjustRebirthSquare, STCirceGlasgowAdjustRebirthSquare, STFileCirceDetermineRebirthSquare, STCirceDiametralAdjustRebirthSquare, STCirceVerticalMirrorAdjustRebirthSquare, STRankCirceOverrideRelevantSide, STRankCirceProjectRebirthSquare, STTakeMakeCirceDetermineRebirthSquares, STTakeMakeCirceCollectRebirthSquaresFork, STTakeMakeCirceCollectRebirthSquares, STAntipodesCirceDetermineRebirthSquare, STSymmetryCirceDetermineRebirthSquare, STPWCDetermineRebirthSquare, STDiagramCirceDetermineRebirthSquare, STContactGridAvoidCirceRebirth, STCirceTestRebirthSquareEmpty, STCircePlacingReborn, STCircePlaceReborn, STSuperCirceNoRebirthFork, STSuperCirceDetermineRebirthSquare, STCirceCageNoCageFork, STCirceCageCageTester, STCirceParrainDetermineRebirth, STCirceContraparrainDetermineRebirth, STCirceRebirthAvoided, STCirceRebirthOnNonEmptySquare, STSupercircePreventRebirthOnNonEmptySquare, STCirceDoneWithRebirth, STCirceVolageRecolorer, STAnticirceConsideringRebirth, STCirceKamikazeCaptureFork, STAnticirceInitialiseRebornFromCapturer, STMarscirceInitialiseRebornFromGenerated, STGenevaInitialiseRebornFromCapturer, STAnticirceCheylanFilter, STAnticirceRemoveCapturer, STMarscirceRemoveCapturer, STSentinellesInserter, STMagicViewsInitialiser, STMagicPiecesRecolorer, STMagicPiecesObserverEnforcer, STSingleboxType2LatentPawnSelector, STSingleboxType2LatentPawnPromoter, STDuellistsRememberDuellist, STHauntedChessGhostSummoner, STHauntedChessGhostRememberer, STGhostChessGhostRememberer, STKobulKingSubstitutor, STSnekSubstitutor, STSnekCircleSubstitutor, STAndernachSideChanger, STAntiAndernachSideChanger, STChameleonPursuitSideChanger, STNorskRemoveIllegalCaptures, STNorskArrivingAdjuster, STProteanPawnAdjuster, STEinsteinArrivingAdjuster, STReverseEinsteinArrivingAdjuster, STAntiEinsteinArrivingAdjuster, STEinsteinEnPassantAdjuster, STTraitorSideChanger, STVolageSideChanger, STMagicSquareSideChanger, STMagicSquareType2SideChanger, STMagicSquareType2AnticirceRelevantSideAdapter, STTibetSideChanger, STDoubleTibetSideChanger, STDegradierungDegrader, STChameleonChangePromoteeInto, STChameleonArrivingAdjuster, STChameleonChessArrivingAdjuster, STLineChameleonArrivingAdjuster, STFrischaufPromoteeMarker, STMarsCirceMoveToRebirthSquare, STMarsCirceMoveGeneratorEnforceRexInclusive, STPhantomAvoidDuplicateMoves, STPlusAdditionalCapturesForPieceGenerator, STMoveForPieceGeneratorAlternativePath, STMoveForPieceGeneratorStandardPath, STMoveForPieceGeneratorPathsJoint, STMoveForPieceGeneratorTwoPaths, STMarsCirceRememberNoRebirth, STMarsCirceRememberRebirth, STMarsCirceFixDeparture, STMarsCirceGenerateFromRebirthSquare, STMoveGeneratorRejectCaptures, STMoveGeneratorRejectNoncaptures, STKamikazeCapturingPieceRemover, STHaanChessHoleInserter, STCastlingChessMovePlayer, STExchangeCastlingMovePlayer, STSuperTransmutingKingTransmuter, STSuperTransmutingKingMoveGenerationFilter, STReflectiveKingsMovesForPieceGenerator, STVaultingKingsMovesForPieceGenerator, STTransmutingKingsMovesForPieceGenerator, STSuperTransmutingKingsMovesForPieceGenerator, STCastlingChessMovesForPieceGenerator, STPlatzwechselRochadeMovesForPieceGenerator, STMessignyMovesForPieceGenerator, STAnnanMovesForPieceGenerator, STFaceToFaceMovesForPieceGenerator, STBackToBackMovesForPieceGenerator, STCheekToCheekMovesForPieceGenerator, STAMUAttackCounter, STAMUObservationCounter, STMutualCastlingRightsAdjuster, STImitatorMover, STImitatorRemoveIllegalMoves, STImitatorDetectIllegalMoves, STBlackChecksNullMoveGenerator, STOutputModeSelector, STOutputPlainTextEndOfTwinWriter, STOutputPlainTextMetaWriter, STOutputPlainTextBoardWriter, STOutputPlainTextPieceCountsWriter, STOutputPlainTextAToBIntraWriter, STOutputPlainTextStartOfTargetWriter, STOutputPlainTextStipulationWriter, STOutputPlainTextStipulationOptionsWriter, STOutputPlainTextRoyalPiecePositionsWriter, STOutputPlainTextNonRoyalAttributesWriter, STOutputPlainTextConditionsWriter, STOutputPlainTextMutuallyExclusiveCastlingsWriter, STOutputPlainTextDuplexWriter, STOutputPlainTextHalfDuplexWriter, STOutputPlainTextQuodlibetWriter, STOutputPlainTextGridWriter, STOutputPlainTextEndOfPositionWriters, STOutputPlaintextTwinIntroWriter, STIllegalSelfcheckWriter, STOutputPlainTextEndOfPhaseWriter, STOutputPlainTextTreeEndOfSolutionWriter, STOutputLaTeXTreeEndOfSolutionWriter, STOutputPlainTextThreatWriter, STOutputLaTeXThreatWriter, STOutputPlainTextMoveWriter, STOutputLaTeXMoveWriter, STOutputPlainTextKeyWriter, STOutputLaTeXKeyWriter, STOutputPlainTextTryWriter, STOutputLaTeXTryWriter, STOutputPlainTextZugzwangWriter, STOutputLaTeXZugzwangWriter, STTrivialEndFilter, STOutputPlaintextTreeRefutingVariationWriter, STOutputPlaintextLineRefutingVariationWriter, STOutputLaTeXTreeRefutingVariationWriter, STOutputPlainTextRefutationsIntroWriter, STOutputPlainTextRefutationWriter, STOutputLaTeXRefutationWriter, STOutputPlaintextTreeCheckWriter, STOutputLaTeXTreeCheckWriter, STOutputPlaintextLineLineWriter, STOutputPlaintextGoalWriter, STOutputPlaintextMoveInversionCounter, STOutputPlaintextMoveInversionCounterSetPlay, STOutputPlaintextLineEndOfIntroSeriesMarker, STOutputLaTeXDiagramWriterBuilder, STOutputLaTeXDiagramWriter, STOutputLaTeXDiagramStartWriter, STOutputLaTeXTwinningWriter, STOutputLaTeXLineLineWriter, STOutputLaTeXGoalWriter, STIsSquareObservedFork, STTestingIfSquareIsObserved, STTestingIfSquareIsObservedWithSpecificWalk, STDetermineObserverWalk, STBicoloresTryBothSides, STOptimisingObserverWalk, STDontTryObservingWithNonExistingWalk, STDontTryObservingWithNonExistingWalkBothSides, STOptimiseObservationsByQueenInitialiser, STOptimiseObservationsByQueen, STUndoOptimiseObservationsByQueen, STTrackBackFromTargetAccordingToObserverWalk, STVaultingKingsEnforceObserverWalk, STVaultingKingIsSquareObserved, STTransmutingKingsEnforceObserverWalk, STTransmutingKingIsSquareObserved, STTransmutingKingDetectNonTransmutation, STReflectiveKingsEnforceObserverWalk, STAnnanEnforceObserverWalk, STFaceToFaceEnforceObserverWalk, STBackToBackEnforceObserverWalk, STCheekToCheekEnforceObserverWalk, STIsSquareObservedTwoPaths, STIsSquareObservedStandardPath, STIsSquareObservedAlternativePath, STIsSquareObservedPathsJoint, STMarsIterateObservers, STMarsCirceIsSquareObservedEnforceRexInclusive, STPlusIsSquareObserved, STMarsIsSquareObserved, STIsSquareObservedOrtho, STValidatingCheckFork, STValidatingCheck, STValidatingObservationFork, STValidatingObservation, STEnforceObserverWalk, STUnderworldResetter, STHuntersResetter, STEnforceHunterDirection, STBrunnerValidateCheck, STValidatingObservationUltraMummer, STValidatingObserverFork, STValidatingObserver, STValidatingObservationGeometryFork, STValidatingObservationGeometry, STValidatingObservationGeometryByPlayingMove, STValidateCheckMoveByPlayingCapture, STMoveTracer, STMoveCounter, nr_slice_types, no_slice_type = nr_slice_types
} slice_type;
extern char const *slice_type_names[];
