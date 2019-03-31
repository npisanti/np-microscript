
----------------------------------------------------
function setup()

end

----------------------------------------------------
function draw()


    mg.strokeWidth( 0.05 )
    mg.setCapRound() -- butt / round / square
    mg.setJoinMiter() --miter / round / bevel 

    mg.center()
    
    mg.strokeA()    
    local offset = 0.1
    local side = 0.05
    mg.begin()
        --mg.poly( 0.0, 0.0, 0.15 + offset*3, 4 )
    mg.close()

    for i=1,3 do 
        local m0 = lfo.triangle( 0.13 + i*0.019 )
        mg.stroke( 1.0, m0*m0 )
        mg.begin()
            mg.poly( 0.0, offset*i,  side, 4 )
            mg.poly( 0.0, -offset*i, side, 4 )
        mg.close()
        
        local m1 = lfo.triangle( 0.2 + i*0.017 ) 
        mg.stroke( 1.0, m1*m1 )
        mg.begin()
            mg.poly( offset*i, 0.0, side, 4 )
            mg.poly( -offset*i, 0.0, side, 4 )
        mg.close()
    end

end

----------------------------------------------------
function exit()

end


