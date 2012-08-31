/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

/*
 * This file is based on WME Lite.
 * http://dead-code.org/redir.php?target=wmelite
 * Copyright (c) 2011 Jan Nedoma
 */

#include "engines/wintermute/base/scriptables/script_ext_math.h"
#include "engines/wintermute/base/scriptables/script_stack.h"
#include "engines/wintermute/base/scriptables/script_value.h"
#include "engines/wintermute/persistent.h"
#include "common/math.h"
#include <math.h>

namespace Wintermute {

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


IMPLEMENT_PERSISTENT(SXMath, true)

BaseScriptable *makeSXMath(BaseGame *inGame) {
	return new SXMath(inGame);
}

//////////////////////////////////////////////////////////////////////////
SXMath::SXMath(BaseGame *inGame) : BaseScriptable(inGame) {

}


//////////////////////////////////////////////////////////////////////////
SXMath::~SXMath() {

}


//////////////////////////////////////////////////////////////////////////
bool SXMath::scCallMethod(ScScript *script, ScStack *stack, ScStack *thisStack, const char *name) {
	//////////////////////////////////////////////////////////////////////////
	// Abs
	//////////////////////////////////////////////////////////////////////////
	if (strcmp(name, "Abs") == 0) {
		stack->correctParams(1);
		stack->pushFloat(fabs(stack->pop()->getFloat()));
		return STATUS_OK;
	}

	//////////////////////////////////////////////////////////////////////////
	// Acos
	//////////////////////////////////////////////////////////////////////////
	else if (strcmp(name, "Acos") == 0) {
		stack->correctParams(1);
		stack->pushFloat(acos(stack->pop()->getFloat()));
		return STATUS_OK;
	}

	//////////////////////////////////////////////////////////////////////////
	// Asin
	//////////////////////////////////////////////////////////////////////////
	else if (strcmp(name, "Asin") == 0) {
		stack->correctParams(1);
		stack->pushFloat(asin(stack->pop()->getFloat()));
		return STATUS_OK;
	}

	//////////////////////////////////////////////////////////////////////////
	// Atan
	//////////////////////////////////////////////////////////////////////////
	else if (strcmp(name, "Atan") == 0) {
		stack->correctParams(1);
		stack->pushFloat(atan(stack->pop()->getFloat()));
		return STATUS_OK;
	}

	//////////////////////////////////////////////////////////////////////////
	// Atan2
	//////////////////////////////////////////////////////////////////////////
	else if (strcmp(name, "Atan2") == 0) {
		stack->correctParams(2);
		double y = stack->pop()->getFloat();
		double x = stack->pop()->getFloat();
		stack->pushFloat(atan2(y, x));
		return STATUS_OK;
	}

	//////////////////////////////////////////////////////////////////////////
	// Ceil
	//////////////////////////////////////////////////////////////////////////
	else if (strcmp(name, "Ceil") == 0) {
		stack->correctParams(1);
		stack->pushFloat(ceil(stack->pop()->getFloat()));
		return STATUS_OK;
	}

	//////////////////////////////////////////////////////////////////////////
	// Cos
	//////////////////////////////////////////////////////////////////////////
	else if (strcmp(name, "Cos") == 0) {
		stack->correctParams(1);
		stack->pushFloat(cos(degreeToRadian(stack->pop()->getFloat())));
		return STATUS_OK;
	}

	//////////////////////////////////////////////////////////////////////////
	// Cosh
	//////////////////////////////////////////////////////////////////////////
	else if (strcmp(name, "Cosh") == 0) {
		stack->correctParams(1);
		stack->pushFloat(cosh(degreeToRadian(stack->pop()->getFloat())));
		return STATUS_OK;
	}

	//////////////////////////////////////////////////////////////////////////
	// Exp
	//////////////////////////////////////////////////////////////////////////
	else if (strcmp(name, "Exp") == 0) {
		stack->correctParams(1);
		stack->pushFloat(exp(stack->pop()->getFloat()));
		return STATUS_OK;
	}

	//////////////////////////////////////////////////////////////////////////
	// Floor
	//////////////////////////////////////////////////////////////////////////
	else if (strcmp(name, "Floor") == 0) {
		stack->correctParams(1);
		stack->pushFloat(floor(stack->pop()->getFloat()));
		return STATUS_OK;
	}

	//////////////////////////////////////////////////////////////////////////
	// Log
	//////////////////////////////////////////////////////////////////////////
	else if (strcmp(name, "Log") == 0) {
		stack->correctParams(1);
		stack->pushFloat(log(stack->pop()->getFloat()));
		return STATUS_OK;
	}

	//////////////////////////////////////////////////////////////////////////
	// Log10
	//////////////////////////////////////////////////////////////////////////
	else if (strcmp(name, "Log10") == 0) {
		stack->correctParams(1);
		stack->pushFloat(log10(stack->pop()->getFloat()));
		return STATUS_OK;
	}

	//////////////////////////////////////////////////////////////////////////
	// Pow
	//////////////////////////////////////////////////////////////////////////
	else if (strcmp(name, "Pow") == 0) {
		stack->correctParams(2);
		double x = stack->pop()->getFloat();
		double y = stack->pop()->getFloat();

		stack->pushFloat(pow(x, y));
		return STATUS_OK;
	}

	//////////////////////////////////////////////////////////////////////////
	// Sin
	//////////////////////////////////////////////////////////////////////////
	else if (strcmp(name, "Sin") == 0) {
		stack->correctParams(1);
		stack->pushFloat(sin(degreeToRadian(stack->pop()->getFloat())));
		return STATUS_OK;
	}

	//////////////////////////////////////////////////////////////////////////
	// Sinh
	//////////////////////////////////////////////////////////////////////////
	else if (strcmp(name, "Sinh") == 0) {
		stack->correctParams(1);
		stack->pushFloat(sinh(degreeToRadian(stack->pop()->getFloat())));
		return STATUS_OK;
	}

	//////////////////////////////////////////////////////////////////////////
	// Tan
	//////////////////////////////////////////////////////////////////////////
	else if (strcmp(name, "Tan") == 0) {
		stack->correctParams(1);
		stack->pushFloat(tan(degreeToRadian(stack->pop()->getFloat())));
		return STATUS_OK;
	}

	//////////////////////////////////////////////////////////////////////////
	// Tanh
	//////////////////////////////////////////////////////////////////////////
	else if (strcmp(name, "Tanh") == 0) {
		stack->correctParams(1);
		stack->pushFloat(tanh(degreeToRadian(stack->pop()->getFloat())));
		return STATUS_OK;
	}

	//////////////////////////////////////////////////////////////////////////
	// Sqrt
	//////////////////////////////////////////////////////////////////////////
	else if (strcmp(name, "Sqrt") == 0) {
		stack->correctParams(1);
		stack->pushFloat(sqrt(stack->pop()->getFloat()));
		return STATUS_OK;
	}

	//////////////////////////////////////////////////////////////////////////
	// DegToRad
	//////////////////////////////////////////////////////////////////////////
	else if (strcmp(name, "DegToRad") == 0) {
		stack->correctParams(1);
		stack->pushFloat(degreeToRadian(stack->pop()->getFloat()));
		return STATUS_OK;
	}

	//////////////////////////////////////////////////////////////////////////
	// RadToDeg
	//////////////////////////////////////////////////////////////////////////
	else if (strcmp(name, "RadToDeg") == 0) {
		stack->correctParams(1);
		stack->pushFloat(radianToDegree(stack->pop()->getFloat()));
		return STATUS_OK;
	} else {
		return STATUS_FAILED;
	}
}


//////////////////////////////////////////////////////////////////////////
ScValue *SXMath::scGetProperty(const char *name) {
	_scValue->setNULL();

	//////////////////////////////////////////////////////////////////////////
	// Type
	//////////////////////////////////////////////////////////////////////////
	if (strcmp(name, "Type") == 0) {
		_scValue->setString("math");
		return _scValue;
	}

	//////////////////////////////////////////////////////////////////////////
	// PI
	//////////////////////////////////////////////////////////////////////////
	else if (strcmp(name, "PI") == 0) {
		_scValue->setFloat(M_PI);
		return _scValue;
	} else {
		return _scValue;
	}
}


//////////////////////////////////////////////////////////////////////////
double SXMath::degreeToRadian(double value) {
	return value * (M_PI / 180.0f);
}


//////////////////////////////////////////////////////////////////////////
double SXMath::radianToDegree(double value) {
	return value * (180.0f / M_PI);
}


//////////////////////////////////////////////////////////////////////////
bool SXMath::persist(BasePersistenceManager *persistMgr) {

	BaseScriptable::persist(persistMgr);
	return STATUS_OK;
}

} // end of namespace Wintermute
