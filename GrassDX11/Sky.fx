//
// Procedural sky fragment shader
//
// Author: Alex V. Boreskoff
//

varying	vec3 	v;
varying	vec3 	l;
varying	vec3 	colorYxy;
varying	float	lv;						// dot (  l, v )
uniform	float	colorExp;

vec3	convertColor ()
{
	vec3	clrYxy = vec3 ( colorYxy );
													// now rescale Y component
	clrYxy [0] = 1.0 - exp ( -clrYxy [0] / colorExp );

	float	ratio    = clrYxy [0] / clrYxy [2];		// Y / y = X + Y + Z
	vec3	XYZ;

	XYZ.x = clrYxy [1] * ratio;						// X = x * ratio
	XYZ.y = clrYxy [0];								// Y = Y
	XYZ.z = ratio - XYZ.x - XYZ.y;					// Z = ratio - X - Y

	const	vec3	rCoeffs = vec3 ( 3.240479, -1.53715, -0.49853  );
	const	vec3	gCoeffs = vec3 ( -0.969256, 1.875991, 0.041556 );
	const	vec3	bCoeffs = vec3 ( 0.055684, -0.204043, 1.057311 );

	return	vec3 ( dot ( rCoeffs, XYZ ), dot ( gCoeffs, XYZ ), dot ( bCoeffs, XYZ ) );
}

void main ()
{
	gl_FragColor = vec4	( clamp ( convertColor (), 0.0, 1.0 ), 1.0 );
}

