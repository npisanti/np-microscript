
----------------------------------------------------
function setup()

end

----------------------------------------------------
function draw()
    us.relative()
    
    us.clear()
    
    us.strokeWidth( 0.05 )
    us.setCapRound() -- butt / round / square
    us.setJoinMiter() --miter / round / bevel 

    us.stroke()    
    local offset = 0.1
    local side = 0.05
    us.begin()
        --us.poly( 0.0, 0.0, 0.15 + offset*3, 4 )
    us.close()

    for i=1,3 do 
        local m0 = lfo.triangle( 0.13 + i*0.019 )
        us.stroke( 1.0, m0*m0 )
        us.begin()
            us.poly( 0.0, offset*i,  side, 4 )
            us.poly( 0.0, -offset*i, side, 4 )
        us.close()
        
        local m1 = lfo.triangle( 0.2 + i*0.017 ) 
        us.stroke( 1.0, m1*m1 )
        us.begin()
            us.poly( offset*i, 0.0, side, 4 )
            us.poly( -offset*i, 0.0, side, 4 )
        us.close()
    end
end

----------------------------------------------------
function exit()

end


