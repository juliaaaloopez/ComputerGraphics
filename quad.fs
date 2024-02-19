varying vec2 v_uv;
//we can use time but we can use also an integer
uniform float u_time;

void main()
{
    //fragment shader
    //argv alpha value vector 4
    //A
    //gl_FragColor = vec4(v_uv.x, 0.0, 1.0-v_uv.x, 0.0); //everything RED if first component is 1.0
    //if we put v_uv.x we will have a horizontal gradient
    //with sinus we change the instensity of one of the colors
    //we overlap the two colors by adding 1.0-v_uv.x
    
    /*
     //B
    vec2 center = vec2(0.5); //we will define our center (of rectangle)
    float dist_ = distance(center, v_uv);
    vec3 final_color = vec3(dist_);
    gl_FragColor = vec4(final_color, 0.0);*/
    
    /*
    //C
    float blur = 0.15;
    float red = smoothstep(0.4 - blur, 0.4, fract(v_uv.x * 5.0)) - smoothstep(0.6, 0.6 + blur,fract(v_uv.x * 5.0));
    float blue = smoothstep(0.4 - blur, 0.4, fract(v_uv.y * 5.0)) - smoothstep(0.6, 0.6 + blur,fract(v_uv.y * 5.0));
    gl_FragColor = vec4(red, 0.0, blue, 1.0);*/
    
    //D
    
    vec2 uv = v_uv * 16.0;
    /*float red = smoothstep(0.5, 0.75, uv.x) * smoothstep(0.5, 0.75, uv.y);
    float green = 1.0 - smoothstep(0.5, 0.75, uv.x) * smoothstep(0.5, 0.75, uv.y);
    float blue = 0.0;
    float alpha = 0.0;
    vec3 color = vec3(red, green, blue);*/
    float diagonal = 1.0 + (uv.x + uv.y);
   
    gl_FragColor = vec4(diagonal * 0.045, 1.0 - (diagonal * 0.045), 0.0, 1.0);
    
    //E
    /*vec2 uv = v_uv * 16.0; //number of squares in row/column
    bool black = mod(floor(uv.x) + floor(uv.y), 2.0) < 1.0; //check if even or odd
    gl_FragColor = black ? vec4(0.0, 0.0, 0.0, 1.0) : vec4(1.0, 1.0, 1.0, 1.0);*/
    
    //F
    
    
    
    
    
}
