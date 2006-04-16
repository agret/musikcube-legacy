///////////////////////////////////////////////////
// 
// Info:
//
//   musik is a cross platform, open source
//   multimedia library. More information at:
//
//     http://www.musikcube.com
//
// Copyright and Credits:
//
//   Copyright      : Casey Langen, 2002-2004
//   Casey Langen   : Lead Developer, Project Manager. E-Mail: casey at musikcube dot com
//   Dustin Carter  : Developer
//   Simon Windmill : Developer
//
// License:
//
//   See license.txt included with this distribution
//
///////////////////////////////////////////////////

#include "stdafx.h"
#include "../include/musikFunctor.h"

///////////////////////////////////////////////////

using namespace musikCore;

///////////////////////////////////////////////////

Functor::Functor()
{
	// virtual
}

///////////////////////////////////////////////////

Functor::~Functor()
{
	// virtual
}

///////////////////////////////////////////////////

void Functor::OnNewSong()
{
	// virtual
}

///////////////////////////////////////////////////

void Functor::OnPause()
{
	// virtual
}

///////////////////////////////////////////////////

void Functor::OnResume()
{
	// virtual
}

///////////////////////////////////////////////////

void Functor::OnStop()
{
	// virtual
}

///////////////////////////////////////////////////

void Functor::OnTaskStart()
{
	// virtual
}

///////////////////////////////////////////////////

void Functor::OnTaskEnd( Task* task_addr )
{
	// virtual
}

///////////////////////////////////////////////////

void Functor::OnTaskProgress( size_t progress, Task* task_addr )
{
	// virtual
}

///////////////////////////////////////////////////

void Functor::OnPlaybackFailed()
{
	// virtual
}

///////////////////////////////////////////////////

void Functor::OnNewEqualizer()
{
	// virtual
}

///////////////////////////////////////////////////

void Functor::OnAlarmTrigger()
{
	// virtual
}

///////////////////////////////////////////////////

void Functor::OnSeek()
{
	// virtual
}

///////////////////////////////////////////////////

bool Functor::VerifyPlaylist( void* pl_addr )
{
	return true;
}

///////////////////////////////////////////////////

