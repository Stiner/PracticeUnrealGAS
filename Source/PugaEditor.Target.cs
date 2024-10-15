// Copyright by Stiner. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class PugaEditorTarget : TargetRules
{
	public PugaEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("Puga");
	}
}
