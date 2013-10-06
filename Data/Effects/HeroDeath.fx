texture framebuffer
vec3 circle
vec2 screen

effect
{
    vec4 pixel = framebuffer(_in);
    
    vec2 pixel_pos = vec2( _in.x*screen.x, _in.y*screen.y );

	float len = length( vec2( circle.x - pixel_pos.x, circle.y - pixel_pos.y ) );

	if ( len > circle.z )
		_out = vec4( 0.0, 0.0, 0.0, 1.0 );
	else
		_out = pixel;
}