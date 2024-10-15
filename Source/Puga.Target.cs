// Copyright by Stiner. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class PugaTarget : TargetRules
{
	public PugaTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("Puga");
	}
}
