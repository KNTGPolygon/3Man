texture framebuffer

effect
{
    vec4 pixel = framebuffer(_in);

	pixel.rgb = vec3( dot( pixel.rgb, vec3(0.3, 0.59, 0.11) ) );
	_out = pixel;
}