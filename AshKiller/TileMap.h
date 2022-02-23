#ifndef TILEMAP_H_INCLUDED
#define TILEMAP_H_INCLUDED

#include<iostream>
#include<fstream>
#include<cctype>
#include<string>
#include<vector>
#include<sstream>

class TileMap
{
private:
    std::vector<std::vector<sf::Vector2i>>map;
    std::vector<sf::Vector2i>tempMap;
    sf::Texture tileTexture;
    sf::Sprite tiles;
    std::string filename = "Map1.txt";
public:

    TileMap()
    {
        initialaze(filename);
    }

    void initialaze(std::string filename){

        std::ifstream openfile(filename);
        tempMap.clear();
        map.clear();

        if(openfile.is_open())
        {

            std::string tileLocation;
            openfile>>tileLocation;
            tileTexture.loadFromFile(tileLocation);
            tiles.setTexture(tileTexture);

            std::cout<<tileLocation<<"\n";

            while(!openfile.eof())
            {

                std::string str, value;
                std::getline(openfile,str);
                std::stringstream stream(str);

                while(std::getline(stream,value,' '))
                {
                    if(value.length()>0)
                    {
                        std::string xx = value.substr(0,value.find(','));
                        std::string yy = value.substr(value.find(',')+1);
                        int x,y,i,j;

                        for(i=0; i<xx.length(); i++)
                        {

                            if(!isdigit(xx[i]))
                                break;
                        }
                        for(j=0; j<yy.length(); j++)
                        {

                            if(!isdigit(yy[j]))
                                break;
                        }

                        x= ( i==xx.length()) ? atoi(xx.c_str()) : -1;
                        y= ( j==yy.length()) ? atoi(yy.c_str()) : -1;
                        tempMap.push_back(sf::Vector2i(x,y));
                    }
                }

                map.push_back(tempMap);
                tempMap.clear();
            }


        }

    }

    void draw(sf::RenderTarget& target)
    {
        for(int i = 0; i< map.size(); i++)
        {
            for(int j = 0; j< map[i].size(); j++)
            {

                if(map[i][j].x != -1 && map[i][j].y != -1)
                {

                    tiles.setTextureRect(sf::IntRect(map[i][j].x *16, map[i][j].y * 16, 16, 16));
                    tiles.setPosition(j*32, i*32);
                    tiles.setScale(2.f,2.f);
                    target.draw(tiles);
                }
            }
        }
    }

};



#endif // TILEMAP_H_INCLUDED
