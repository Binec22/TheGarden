#include "calque.h"

void Calque::setUpTiles(RenderWindow &window, const View& view)
{
    sf::FloatRect viewBounds(view.getCenter() - view.getSize() / 2.f, view.getSize());

    sf::Vector2i startTile(std::max(int(viewBounds.left / TILE_SIZE), 0), std::max(int(viewBounds.top / TILE_SIZE), 0));
    sf::Vector2i endTile( std::min(int((viewBounds.left + viewBounds.width) / TILE_SIZE), 119), std::min(int((viewBounds.top + viewBounds.height) / TILE_SIZE), 89));

    for (int i = startTile.y; i <= endTile.y; ++i) {
        for (int j = startTile.x; j <= endTile.x; ++j) {
            if(!(this->tuiles[i][j] == nullptr))
                window.draw(this->tuiles[i][j]->getTileSprite());
        }
    }
}

void Calque::drawPlants(RenderWindow &window, const View &view, float &currentTime)
{
    sf::FloatRect viewBounds(view.getCenter() - view.getSize() / 2.f, view.getSize());

    sf::Vector2i startTile(std::max(int(viewBounds.left / TILE_SIZE), 0), std::max(int(viewBounds.top / TILE_SIZE), 0));
    sf::Vector2i endTile( std::min(int((viewBounds.left + viewBounds.width) / TILE_SIZE), 119), std::min(int((viewBounds.top + viewBounds.height) / TILE_SIZE), 89));
    for (int i = startTile.y; i <= endTile.y; ++i) {
        for (int j = startTile.x; j <= endTile.x; ++j) {
            if(!(this->tuiles[i][j] == nullptr))
            {
                this->tuiles[i][j]->updateMaturity(currentTime);
                int maturity = this->tuiles[i][j]->getMaturity();
                int posY;
                switch (this->tuiles[i][j]->getValeur())
                {
                case BEETROOT_SEED:
                    posY = 0;
                    break;
                case POTATOE_SEED:
                    posY = 7;
                    break;
                
                default:
                    break;
                }
                this->tuiles[i][j]->setTileSprite(IntRect(maturity * TILE_SIZE,posY * TILE_SIZE,TILE_SIZE,TILE_SIZE));
                  
                window.draw(this->tuiles[i][j]->getTileSprite());
            }
        }
    }
}

Calque::Calque(int calqueNumber)
{
    this->calqueNumber = calqueNumber;
    this->selectCalque();
    this->readCSV();
    this->constructCalque();
}

Image Calque::getImage(void)
{
    return sf::Image();
}

void Calque::setImage(Image image)
{
	this->imageCalque = image;
}


Calque& Calque::operator=(const Calque& newCalque) {
    if (this != &newCalque) {
        this->fileName = newCalque.fileName;
        this->calqueTexture = newCalque.calqueTexture;
        this->tilesByLine = newCalque.tilesByLine;
        this->values = newCalque.values;
        this->width = newCalque.width;
        this->height = newCalque.height;

        this->tuiles.clear();
        for (int i = 0; i < this->height; i++) {
            std::vector<Tile*> tmpRow;
            for (int j = 0; j < this->width; j++) {
                tmpRow.push_back(new Tile(*newCalque.tuiles[i][j])); 
            }
            this->tuiles.push_back(tmpRow);
        }
    }
    return *this;
}


Calque::~Calque()
{
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
			delete this->tuiles[i][j];
        }
    }
}

void Calque::selectCalque()
{
    /*****************************************************************************************/
    /* Récupération de la map au format .csv et du spritesheet associé en fonction du calque */
    /*****************************************************************************************/
    Texture textTmp;
    Image imageTmp;
    switch (this->calqueNumber)
    {
    case 1:
        this->fileName = "map/maisons_calque1.csv";
        this->calqueTextureName = "graphics/sols.png";
        this->tilesByLine = 9;
		if(!this->imageCalque.loadFromFile(this->calqueTextureName))
			cout << "Erreur lors du chargement de la texture du calque 1" << endl;
        
        textTmp.loadFromImage(this->imageCalque, IntRect((12 % this->tilesByLine * TILE_SIZE) , (12 / this->tilesByLine * TILE_SIZE), TILE_SIZE, TILE_SIZE));
        Grass::initializeGrassTexture(textTmp);
        textTmp.loadFromImage(this->imageCalque, IntRect((141 % this->tilesByLine * TILE_SIZE) , (141 / this->tilesByLine * TILE_SIZE), TILE_SIZE, TILE_SIZE));
        Farmland::initializeFarmlandTexture(textTmp);

        break;
    
    case 2:
        this->fileName = "map/maisons_calque2.csv";
        this->calqueTextureName = "graphics/sols.png";
        this->tilesByLine = 9;
		if(!this->imageCalque.loadFromFile(this->calqueTextureName))
			cout << "Erreur lors du chargement de la texture du calque 2" << endl;
        break;
        
    case 3:
        this->fileName = "map/maisons_calque3.csv";
        this->calqueTextureName = "graphics/maison.png";
        this->tilesByLine = 9;
		if(!this->imageCalque.loadFromFile(this->calqueTextureName))
			cout << "Erreur lors du chargement de la texture du calque 3" << endl;
        
        textTmp.loadFromImage(this->imageCalque, IntRect((47 % this->tilesByLine * TILE_SIZE) , (47 / this->tilesByLine * TILE_SIZE), TILE_SIZE, TILE_SIZE));
        Rock::initializeRockTexture(textTmp);

        break;

    case 4:
        this->fileName = "map/maisons_calque3.csv";
        this->calqueTextureName = "graphics/crop.png";
        this->tilesByLine = 12;
		if(!this->imageCalque.loadFromFile(this->calqueTextureName))
			cout << "Erreur lors du chargement de la texture du calque 4" << endl;
        textTmp.loadFromImage(this->imageCalque);
        Plant::loadPlantImage(textTmp);
        break;

    default:
        break;
    }
}

void Calque::readCSV()
{
    /**********************************************************************************************************/
    /* LECTURE DU FICHIER .CSV CONTENANT LA MAP ET CREATION D'UN VECTEUR 2D CONTENANT LES VALEURS DES SPRITES */
    /**********************************************************************************************************/
    

	fstream fin;	//On crée un flux (stream) pour lire le fichier
	vector < int > vectTmp; //vecteur temporaire pour lire une ligne
	string strBuf, strTmp;	//chaînes de caractères temporaires
	stringstream iostr;	//On crée un stringstream pour gérer nos chaînes
	fin.open(this->fileName, fstream::in); //On ouvre le fichier

	if (!fin.is_open())
	{
		std::cerr << "Erreur de chargement du fichier.\n";
		exit(1);
	}

	//On lit notre fichier jusqu'à la fin (eof = end of file)
	while (!fin.eof())
	{
		getline(fin, strBuf);   //On récupère la ligne dans la chaîne strBuf

		if (!strBuf.size()) //Si la ligne est vide, on continue la boucle
			continue;

		iostr.clear();	//Sinon on poursuit et on réinitialise notre stringstream
		iostr.str(strBuf);  //On y envoie le contenu du buffer strBuf

		vectTmp.clear();

		//On boucle pour lire chaque numéro de tile du fichier map
		while (true)
		{
			//Pour chaque ligne on récupère le numéro de la tile, en les parsant grâce aux virgules qui les séparent
			getline(iostr, strTmp, ',');

			vectTmp.push_back(atoi(strTmp.c_str()));

			if (!iostr.good()) break;
		}

		//Si le vecteur ligne n'est pas vide, on l'envoie dans notre vecteur à 2 dimensions
		if (vectTmp.size())
			this->values.push_back(vectTmp);
	}
	fin.close();	//On ferme le fichier

    this->width = this->values[0].size();
    this->height = this->values.size();
}

void Calque::constructCalque()
{
    /*********************************************************************************/
    /* Création du vecteur 2D de Tuiles à partir des valeurs récupérées précédemment */
    /*********************************************************************************/

    vector<Tile *> tmpRow;
    Texture textTmp;

    switch (this->calqueNumber)
    {
    case 1:
        for (int i = 0; i < this->height; i++) 
        {
            tmpRow.clear();
            for (int j = 0; j < this->width; j++) 
            {
                Vector2f tilePosition(j * TILE_SIZE,i * TILE_SIZE);

                if(this->values[i][j] == -1)
                {
                    tmpRow.push_back(nullptr);  
                }
                else if(this->values[i][j] == 12)
                    tmpRow.push_back(new Grass(tilePosition, this->values[i][j]));
                else
                {
                    textTmp.loadFromImage(this->imageCalque, IntRect((this->values[i][j] % this->tilesByLine * TILE_SIZE) , (this->values[i][j] / this->tilesByLine * TILE_SIZE), TILE_SIZE, TILE_SIZE));
                    tmpRow.push_back(new Tile(textTmp, tilePosition, this->values[i][j]));
                }
            }
            this->tuiles.push_back(tmpRow);
        }      
        break;

    case 2:
        for (int i = 0; i < this->height; i++) 
        {
            tmpRow.clear();
            for (int j = 0; j < this->width; j++) 
            {
                Vector2f tilePosition(j * TILE_SIZE,i * TILE_SIZE);

                if(this->values[i][j] == -1)
                {
                    tmpRow.push_back(nullptr);  
                }
                else if(this->values[i][j] == 12)
                    tmpRow.push_back(new Grass(tilePosition, this->values[i][j]));
                else
                {
                    textTmp.loadFromImage(this->imageCalque, IntRect((this->values[i][j] % this->tilesByLine * TILE_SIZE) , (this->values[i][j] / this->tilesByLine * TILE_SIZE), TILE_SIZE, TILE_SIZE));
                    tmpRow.push_back(new Tile(textTmp, tilePosition, this->values[i][j]));
                }
            }
            this->tuiles.push_back(tmpRow);
        }      
        break;

    case 3:
        for (int i = 0; i < this->height; i++) 
        {
            tmpRow.clear();
            for (int j = 0; j < this->width; j++) 
            {
            Vector2f tilePosition(j * TILE_SIZE,i * TILE_SIZE);
                if(this->values[i][j] == -1)
                {
                    tmpRow.push_back(nullptr);  
                }
                else if(this->values[i][j] == 47)
                    tmpRow.push_back(new Rock(tilePosition, this->values[i][j]));
                else if(this->values[i][j] == 38 || this->values[i][j] == 39 || this->values[i][j] == 48)
                {
                    textTmp.loadFromImage(imageCalque, IntRect((this->values[i][j] % this->tilesByLine * TILE_SIZE) , (this->values[i][j] / this->tilesByLine * TILE_SIZE), TILE_SIZE, TILE_SIZE));
                    tmpRow.push_back(new Tile(textTmp, tilePosition, this->values[i][j], 200.0f));                        
                }
                else
                {
                    textTmp.loadFromImage(imageCalque, IntRect((this->values[i][j] % this->tilesByLine * TILE_SIZE) , (this->values[i][j] / this->tilesByLine * TILE_SIZE), TILE_SIZE, TILE_SIZE));
                    tmpRow.push_back(new Tile(textTmp, tilePosition, this->values[i][j]));
                }
            }
            this->tuiles.push_back(tmpRow);
        }
        break;

    case 4:
        for (int i = 0; i < this->height; i++) 
        {
            tmpRow.clear();
            for (int j = 0; j < this->width; j++) 
            {
                Vector2f tilePosition(j * TILE_SIZE,i * TILE_SIZE);
                tmpRow.push_back(nullptr);
            }
            this->tuiles.push_back(tmpRow);
        }
        break;
    
    default:
        break;
    }
}
