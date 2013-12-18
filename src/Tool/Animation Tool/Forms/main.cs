﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml;
using System.IO.Compression;
using System.IO;
using Ionic.Zip;
using System.Collections.Specialized;

namespace Animation_Tool
{
    public partial class main : Form
    {
        public main()
        {            
            InitializeComponent();
            init();
        }
        private void init()
        {
            workSpace.Width = 2000;
            workSpace.Height = 2000;

            PlayWindow.Show();
            NewFrame(null, null);

            updateWorkSpace();
            updateTimeline();
        }

        public class frameInfo
        {
            public Point point { get; set; }
            public Size size { get; set; }
            public int rotate { get; set; }
            public int time { get; set; }
            public Bitmap sprite { get; set; }
            public Bitmap oriSprite { get; set; }

            public frameInfo(Point p, Size s, int r, int t)
            {
                point = p;
                size = s;
                rotate = r;
                time = t;
            }
        }

        play PlayWindow = new play();
        List<Bitmap> originalSprites = new List<Bitmap>();
        List<PictureBox> sprites = new List<PictureBox>();
        List<frameInfo> frames = new List<frameInfo>();
        List<PictureBox> timelineImage = new List<PictureBox>();
        PictureBox frameImage = new PictureBox();
        int selectedSprite = 0;
        int allocatedSprite = 0;
        int selectedFrame = 0;

        // Sprite load
        private void spriteAdd(string FileName)
        {
            PictureBox a = new PictureBox();

            originalSprites.Add(new Bitmap(FileName));

            sprites.Add(a);
            a.Click += new System.EventHandler(this.sprite_Click);
            a.DoubleClick += new System.EventHandler(this.sprite_DoubleClick);
            spritePanel.Controls.Add(a);
        }
        private void ButtonSpriteAdd_Click(object sender, EventArgs e)
        {
            OpenFileDialog openImage = new OpenFileDialog();

            openImage.Filter = "Image Files(*.bmp;*.jpg;*.png)|*.bmp;*.jpg;*.png";
            openImage.FilterIndex = 1;
            openImage.RestoreDirectory = true;
            openImage.Multiselect = true;
            openImage.InitialDirectory = System.IO.Directory.GetCurrentDirectory();
            
            if (openImage.ShowDialog() == DialogResult.OK)
            {
                foreach (string filename in openImage.FileNames)
                {
                    spriteAdd(filename);
                }
                updateImageList();                
            }
        }
        private void ButtonSpriteDelete_Click(object sender, EventArgs e)
        {
            if (sprites.Count == 0) return;

            originalSprites[selectedSprite].Dispose();
            sprites[selectedSprite].Dispose();
            originalSprites.RemoveAt(selectedSprite);
            sprites.RemoveAt(selectedSprite);

            if (sprites.Count <= selectedSprite) --selectedSprite;

            updateImageList();
        }
        private void sprite_Click(object sender, EventArgs e)
        {
            PictureBox a = (PictureBox)sender;
            selectedSprite = sprites.FindIndex(delegate(PictureBox s)
            {
                return s.GetHashCode() == a.GetHashCode();
            });
            updateImageList();
        }
        private void sprite_DoubleClick(object sender, EventArgs e)
        {
            if (frameImage != null)
            {
                workSpace.Controls.Remove(frameImage);
                frameImage.Dispose();
            }

            allocatedSprite = selectedSprite;
            frames[allocatedSprite].oriSprite = originalSprites[selectedSprite];
            ResetFrameImage(originalSprites[selectedSprite], new Point((workSpace.Size.Width - originalSprites[selectedSprite].Size.Width) / 2, (workSpace.Size.Height - originalSprites[selectedSprite].Size.Height) / 2));
            updateAttribute();
        }
        private void splitContainer1_SplitterMoved(object sender, SplitterEventArgs e)
        {
            updateImageList();
            updateWorkSpace();
        }
        
        // Update
        private void updateImageList()
        {
            if (sprites.Count == 0)
            {
                selectedSprite = 0;
                return;
            }
            int totalHeight = 0;
            int spriteWidth = splitContainer1.Panel1.Width - 30;//spritePanel.Width;
            int spriteGap = 10;
            Graphics g = null;

            spritePanel.Width = spriteWidth;
            for (int i=0; i<sprites.Count; ++i)
            {
                int spriteHeight = (int)((double)originalSprites[i].Size.Height / (double)originalSprites[i].Size.Width * (double)spriteWidth);
                if (sprites[i].Image != null)
                    sprites[i].Image.Dispose();

                sprites[i].Image = new Bitmap(spriteWidth, spriteHeight);
                g = Graphics.FromImage(sprites[i].Image);
                
                sprites[i].Size = new Size(spriteWidth, spriteHeight);
                sprites[i].Location = new Point(0, totalHeight);
                g.DrawImage(originalSprites[i], new Rectangle(0, 0, spriteWidth, spriteHeight));
                totalHeight += spriteHeight + spriteGap;
            }

            Graphics.FromImage(sprites[selectedSprite].Image).DrawRectangle(new Pen(Color.Red, 8), new Rectangle(0, 0, sprites[selectedSprite].Image.Width, sprites[selectedSprite].Image.Height));
            spritePanel.Height = totalHeight;
            if(g != null)
                g.Dispose();
        }
        private void updateWorkSpace()
        {
            workSpace.Location = new Point((splitContainer1.Panel2.Right - splitContainer1.Panel2.Left) / 2 - workSpace.Size.Width / 2, (splitContainer1.Panel2.Bottom - splitContainer1.Panel2.Top) / 2 - workSpace.Size.Height / 2);

            if (workSpace.Image != null)
                workSpace.Image.Dispose();
            workSpace.Image = new Bitmap(workSpace.Size.Width, workSpace.Size.Height);

            Graphics g = Graphics.FromImage(workSpace.Image);
            Pen pen = new Pen(Color.Black, 1);
            pen.DashStyle = System.Drawing.Drawing2D.DashStyle.Dot;

            g.DrawLine(pen , 0, workSpace.Size.Height / 2, workSpace.Size.Width, workSpace.Size.Height / 2);
            g.DrawLine(pen , workSpace.Size.Width / 2, 0, workSpace.Size.Width / 2, workSpace.Size.Height);
            g.FillRectangle(new SolidBrush(Color.Blue), workSpace.Size.Height / 2 -1 , workSpace.Size.Width / 2-1 , 3 , 3);

            g.Dispose();
        }
        private void updateAttribute()
        {
            AttributeSpriteWidth.ReadOnly = isDrag;
            AttributeSpriteHeight.ReadOnly = isDrag;
            SpriteX.ReadOnly = isDrag;
            SpriteY.ReadOnly = isDrag;

            AttributeSpriteWidth.Text = frameImage.Image.Width.ToString();
            AttributeSpriteHeight.Text = frameImage.Image.Height.ToString();
            SpriteX.Text = (frameImage.Location.X - workSpace.Width / 2).ToString();
            SpriteY.Text = (frameImage.Location.Y - workSpace.Height / 2).ToString();
            AttributeSpriteRotate.Text = frames[selectedFrame].rotate.ToString();
            AttributePlayTime.Text = frames[selectedFrame].time.ToString();

            //updateFrameInfo(new Point(frameImage.Location.X - frameImage.Size.Width / 2, frameImage.Location.Y - frameImage.Size.Height / 2), new Size(frameImage.Size.Width, frameImage.Size.Height), selectedFrame);
        }
        private void updateTimeline()
        {
            int totalWidth = 0;
            int frameHeight = 80;
            int frameWidth = 80;
            int frameGap = 5;
            Graphics g = null;

            for (int i = 0; i < frames.Count; ++i)
            {
                Bitmap bmp = frames[i].sprite;
                if (bmp == null)
                    bmp = new Bitmap(frameHeight, frameHeight);

                frameWidth = (int)((double)bmp.Size.Width / (double)bmp.Size.Height * (double)frameHeight);

                timelineImage[i].Image = new Bitmap(frameWidth, frameHeight);
                g = Graphics.FromImage(timelineImage[i].Image);

                timelineImage[i].Size = new Size(frameHeight, frameHeight);
                timelineImage[i].Location = new Point(totalWidth, 0);
                g.DrawImage(bmp, new Rectangle(0, 0, frameWidth, frameHeight));
                g.DrawString((i + 1).ToString(), DefaultFont, new SolidBrush(Color.Black), new Point(0, 0));
                totalWidth += frameHeight + frameGap;
            }

            Graphics.FromImage(timelineImage[selectedFrame].Image).DrawRectangle(new Pen(Color.Red, 4), new Rectangle(0, 0, frameWidth, frameHeight));
            timelineFrame.Width = totalWidth;
        }
        private void updateFrameInfo(Point p, Size s,int index)
        {
            if (frames.Count == 0)
                return;

            frames[index].point = p;
            frames[index].size = s;
            if(frameImage.Image != null)
                frames[index].sprite = new Bitmap(frameImage.Image);
        }

        // sprite Drag
        bool isDrag = false;
        Point firstPoint = new Point();
        private void spriteDrag(object sender, MouseEventArgs e)
        {
            PictureBox obj = (PictureBox)sender;
            int x = obj.Location.X + (e.X - firstPoint.X);
            int y = obj.Location.Y + (e.Y - firstPoint.Y);

            obj.Location = new Point(x, y);
            updateAttribute();
        }
        private void workSpace_MouseDown(object sender, MouseEventArgs e)
        {
            isDrag = true;
            firstPoint.X = e.X;
            firstPoint.Y = e.Y;
            spriteDrag(sender, e);
        }
        private void workSpace_MouseMove(object sender, MouseEventArgs e)
        {
          //  if()
            if(isDrag)
                spriteDrag(sender, e);
        }
        private void workSpace_MouseUp(object sender, MouseEventArgs e)
        {
            isDrag = false;
            updateAttribute();
        }

        // edit Attribute
        private int convertTextBoxToValue(TextBox box, int value, int low, int high, KeyPressEventArgs e)
        {
            if (!Char.IsDigit(e.KeyChar) && e.KeyChar != '-' && e.KeyChar != Convert.ToChar(Keys.Back) && e.KeyChar != Convert.ToChar(Keys.Enter))
                e.Handled = true;

            if (e.KeyChar != Convert.ToChar(Keys.Enter))
                return -9999;

            try
            {
                int result = Convert.ToInt32(box.Text);

                if (result > high)
                {
                    box.Text = high.ToString();
                    result = high;
                }
                if (result < low)
                {
                    box.Text = low.ToString();
                    result = low;
                }
                box.Text = result.ToString();

                return result;
            }
            catch (Exception ex) 
            { 
                MessageBox.Show(ex.Message);
                box.Text = value.ToString();
                return -9999;
            }
        }
        private void EditAttribute(object sender, KeyPressEventArgs e)
        {
            if (sprites.Count == 0)
                return;

            TextBox box = (TextBox)sender;

            if (sender == SpriteX)
            {
                int result = convertTextBoxToValue(box, frameImage.Left - workSpace.Width / 2, -999, 999, e);
                if (result != -9999)
                    frameImage.Left = result + workSpace.Width / 2;
            }
            else if (sender == SpriteY)
            {
                int result = convertTextBoxToValue(box, frameImage.Top - workSpace.Height / 2, -999, 999, e);
                if (result != -9999)
                    frameImage.Top = result + workSpace.Height / 2;
            }
            else if (sender == AttributeSpriteWidth)
            {
                int result = convertTextBoxToValue(box, frameImage.Size.Width, -999, 999, e);
                if (result != -9999)
                {
                    frameImage.Image = new Bitmap(result, frameImage.Size.Height);
                    Graphics g = Graphics.FromImage(frameImage.Image);
                    frameImage.Size = new Size(result, frameImage.Size.Height);
                    g.DrawImage(originalSprites[allocatedSprite], new Rectangle(0, 0, result, frameImage.Height));
                }
            }
            else if (sender == AttributeSpriteHeight)
            {
                int result = convertTextBoxToValue(box, frameImage.Size.Height, -999, 999, e);
                if (result != -9999)
                {
                    frameImage.Image = new Bitmap(frameImage.Size.Width, result);
                    Graphics g = Graphics.FromImage(frameImage.Image);
                    frameImage.Size = new Size(frameImage.Size.Width, result);
                    g.DrawImage(originalSprites[allocatedSprite], new Rectangle(0, 0, frameImage.Size.Width, result));
                }
            }
            else if (sender == AttributeSpriteRotate)
            {
                int result = convertTextBoxToValue(box, frames[selectedFrame].rotate, -360, 360, e);
                if (result != -9999)
                    frames[selectedFrame].rotate = result;
            }
            else if (sender == AttributePlayTime)
            {
                int result = convertTextBoxToValue(box, frames[selectedFrame].time, 0, 9999, e);
                if (result != -9999)
                    frames[selectedFrame].time = result;
            }
        }

        // timeline
        private void NewFrame(object sender, EventArgs e)
        {
            updateFrameInfo(new Point(frameImage.Location.X - workSpace.Size.Width / 2, frameImage.Location.Y - workSpace.Size.Height / 2), new Size(frameImage.Size.Width, frameImage.Size.Height), selectedFrame);
            //frames.Add(new frameInfo(new Point(0, 0), new Size(0, 0), 100, 0));
            ResetFrame();
            //selectedFrame = frames.Count - 1;

            timelineImage.Add(new PictureBox());
            timelineImage[timelineImage.Count - 1].BorderStyle = BorderStyle.FixedSingle;
            timelineImage[timelineImage.Count - 1].Click += new System.EventHandler(this.FrameChange);
            timelineImage[timelineImage.Count - 1].SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            //timelineImage[timelineImage.Count - 1].DoubleClick += new System.EventHandler(this.Frame_DoubleClick);
            timelineFrame.Controls.Add(timelineImage[timelineImage.Count - 1]);

            FrameChange(timelineImage[timelineImage.Count - 1], null);

            ResetFrameImage(new Bitmap(2, 2), new Point(workSpace.Width/2, workSpace.Height/2));
            updateTimeline();
        }
        private void DeleteFrame(object sender, EventArgs e)
        {
            if (frames.Count > 0)
            {
                frames.RemoveAt(selectedFrame);
                timelineFrame.Controls.Remove(timelineImage[selectedFrame]);
                timelineImage.RemoveAt(selectedFrame);
            }
            if (frames.Count == 0)
                NewFrame(null, null);

            if (frames.Count <= selectedFrame)
                --selectedFrame;

            FrameChange(timelineImage[selectedFrame], null);
        }
        private void ResetFrameImage(Bitmap img, Point location)
        {
            if (!frameImage.IsDisposed)
                frameImage.Dispose();
            frameImage = new PictureBox();
            frameImage.Image = img;
            frameImage.Size = img.Size;
            frameImage.Location = location;

            frameImage.MouseDown += new System.Windows.Forms.MouseEventHandler(this.workSpace_MouseDown);
            frameImage.MouseMove += new System.Windows.Forms.MouseEventHandler(this.workSpace_MouseMove);
            frameImage.MouseUp += new System.Windows.Forms.MouseEventHandler(this.workSpace_MouseUp);

            workSpace.Controls.Add(frameImage);
        }
        private void ResetFrame()
        {
            frames.Add(new frameInfo(new Point(workSpace.Width / 2, workSpace.Height / 2), new Size(1, 1), 100, 0));
            frames[frames.Count - 1].sprite = new Bitmap(2, 2);
        }
        private void FrameChange(object sender, EventArgs e)
        {
            if(e!=null)
                updateFrameInfo(new Point(frameImage.Location.X - workSpace.Size.Width / 2, frameImage.Location.Y - workSpace.Size.Height / 2), new Size(frameImage.Size.Width, frameImage.Size.Height), selectedFrame);

            PictureBox a = (PictureBox)sender;
            selectedFrame = timelineImage.FindIndex(delegate(PictureBox s)
            {
                return s.GetHashCode() == a.GetHashCode();
            });
            ResetFrameImage(frames[selectedFrame].sprite, new Point(frames[selectedFrame].point.X  + workSpace.Width / 2, frames[selectedFrame].point.Y + workSpace.Height / 2));

            updateTimeline();
            updateAttribute();
        }
        private void openPlayWindow(object sender, EventArgs e)
        {
            PlayWindow.Show();
            PlayWindow.playAnimation(frames);
        }

        private void applicationReset()
        {
            foreach (Bitmap temp in originalSprites)
                temp.Dispose();
            foreach (PictureBox temp in sprites)
                temp.Dispose();
            foreach (PictureBox temp in timelineImage)
                temp.Dispose();

            originalSprites.Clear();
            sprites.Clear();
            frames.Clear();
            timelineImage.Clear();

            frameImage.Dispose();
            frameImage = new PictureBox();

            selectedSprite = allocatedSprite = selectedFrame = 0;
            System.GC.Collect();

            PlayWindow.Init();
            init();
        }
        private void newButton_Click(object sender, EventArgs e)
        {
            applicationReset();
        }

        private void loadButton_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog1 = new OpenFileDialog();

            openFileDialog1.Filter = "Animation files|*.ani";
            openFileDialog1.FilterIndex = 0;
            openFileDialog1.RestoreDirectory = true;
            openFileDialog1.InitialDirectory = System.IO.Directory.GetCurrentDirectory();

            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                openAniFile(openFileDialog1.FileName);
                //OpenCSMFile(openFileDialog1.FileName);
            }
        }
        private int findSpriteIndex(Bitmap src)
        {
            int result = originalSprites.FindIndex(delegate(Bitmap s)
               {
                   return s.GetHashCode() == src.GetHashCode();
               });

            return result;
        }
        private void openAniFile(string FileName)
        {
            applicationReset();

            int frameCount = 0, spriteCount = 0;
            Size atlasSize = new Size();
            List<int> spriteIndex = new List<int>();

            string zipToUnpack = FileName;
            MemoryStream ms;

            using (ZipFile zip1 = ZipFile.Read(zipToUnpack))
            {
                foreach (ZipEntry a in zip1)
                {
                    ms = new MemoryStream();
                    a.Extract(ms);
                    ms.Seek(0, SeekOrigin.Begin);

                    // XML
                    if (a.FileName.ToLower().IndexOf(".xml") > 0)
                    {
                        XmlDocument xmldoc = new XmlDocument();
                        xmldoc.Load(ms);

                        XmlNodeList xnList = xmldoc.SelectNodes("animation/Info"); //접근할 노드
                        foreach (XmlNode xn in xnList)
                        {
                            frameCount = Convert.ToInt32(xn["frame"].Attributes["count"].Value);
                            spriteCount = Convert.ToInt32(xn["sprite"].Attributes["count"].Value);
                            atlasSize.Width = Convert.ToInt32(xn["atlas"].Attributes["width"].Value);
                            atlasSize.Height = Convert.ToInt32(xn["atlas"].Attributes["height"].Value);
                        }

                        xnList = xmldoc.SelectNodes("animation/resource"); //접근할 노드
                        foreach (XmlNode xn in xnList)
                        {
                            int index;
                            Point p = new Point();
                            Size s = new Size();
                            int r, t;

                            index = Convert.ToInt32(xn["frame"].Attributes["index"].Value);
                            spriteIndex.Add(Convert.ToInt32(xn["frame"].Attributes["spriteIndex"].Value));
                            p.X = Convert.ToInt32(xn["frame"].Attributes["X"].Value);
                            p.Y = Convert.ToInt32(xn["frame"].Attributes["Y"].Value);
                            s.Width = Convert.ToInt32(xn["frame"].Attributes["Width"].Value);
                            s.Height = Convert.ToInt32(xn["frame"].Attributes["Height"].Value);
                            r = Convert.ToInt32(xn["frame"].Attributes["Rotate"].Value);
                            t = Convert.ToInt32(xn["frame"].Attributes["Time"].Value);

                            frames.Add(new frameInfo(p, s, r, t));
                        }
                    }
                    else
                        spriteAdd(a.FileName);

                    ms.Dispose();
                }
            } 
            for (int i = 0; i < frameCount; ++i)
            {
                Bitmap temp = new Bitmap(frames[i].size.Width, frames[i].size.Height);
                Graphics.FromImage(temp).DrawImage(originalSprites[spriteIndex[i]], new Rectangle(0, 0, frames[i].size.Width, frames[i].size.Height));
                frames[i].sprite = temp;
            }
            updateTimeline();
            updateImageList();


            /*
            int usedTileSetCount = 0;
            string zipToUnpack = FileName;
            MemoryStream ms;

            TileList.Clear();
            using (ZipFile zip1 = ZipFile.Read(zipToUnpack))
            {
                foreach (ZipEntry a in zip1)
                {
                    ms = new MemoryStream();
                    a.Extract(ms);
                    ms.Seek(0, SeekOrigin.Begin);

                    // XML
                    if (a.FileName.ToLower().IndexOf(".xml") > 0)
                    {
                        XmlDocument xmldoc = new XmlDocument();
                        xmldoc.Load(ms);

                        XmlNodeList xnList = xmldoc.SelectNodes("map/mapInfo"); //접근할 노드
                        foreach (XmlNode xn in xnList)
                        {
                            mainMap.MapSize.Width = Convert.ToInt32(xn["size"].Attributes["width"].Value);
                            mainMap.MapSize.Height = Convert.ToInt32(xn["size"].Attributes["height"].Value);
                            usedTileSetCount = Convert.ToInt32(xn["usedTileSet"].Attributes["count"].Value);
                        }
                        mainMap_init(mainMap.MapSize.Width, mainMap.MapSize.Height);

                        for (int i = 0; i < mainMap.MapSize.Width; ++i)
                        {
                            for (int j = 0; j < mainMap.MapSize.Height; ++j)
                            {
                                xnList = xmldoc.SelectNodes("map/tileInfo/t" + i.ToString() + "-" + j.ToString());
                                mainMap.grid[i, j].isFull = xmldoc.SelectSingleNode("map/tileInfo/t" + i.ToString() + "-" + j.ToString()).Attributes["isFull"].InnerText == "true" ? true : false;

                                if (!mainMap.grid[i, j].isFull)
                                    continue;

                                foreach (XmlNode xn in xnList)
                                {
                                    //mainMap.grid[i, j].Attribute = Convert.ToInt32(attribute);
                                    mainMap.grid[i, j].TIleSetID = Convert.ToInt32(xn["TileImageInfo"].Attributes["Index"].InnerText);
                                    mainMap.grid[i, j].TileLocation.X = Convert.ToInt32(xn["TileImageInfo"].Attributes["X"].InnerText);
                                    mainMap.grid[i, j].TileLocation.Y = Convert.ToInt32(xn["TileImageInfo"].Attributes["Y"].InnerText);
                                    mainMap.grid[i, j].attributeMove = xn["Attribute"].Attributes["move"].InnerText == "true" ? true : false;
                                    mainMap.grid[i, j].attributeHeight = Convert.ToInt32(xn["Attribute"].Attributes["height"].InnerText);
                                }
                            }
                        }
                    }
                    else
                        TileList.Add(new BitmapList(bitmapID++, new Bitmap(ms)));

                    ms.Dispose();
                }

            }
            for (int i = 0; i < mainMap.MapSize.Width; ++i)
            {
                for (int j = 0; j < mainMap.MapSize.Height; ++j)
                {
                    if (mainMap.grid[i, j].isFull)
                        mainMap.grid[i, j].tile = TileList[mainMap.grid[i, j].TIleSetID].image.Clone(new Rectangle(new Point(mainMap.grid[i, j].TileLocation.X, mainMap.grid[i, j].TileLocation.Y), new Size(TileSize, TileSize)), TileList[mainMap.grid[i, j].TIleSetID].image.PixelFormat);
                }
            }

            TileSelectWindow.changeImage(TileList.Count - 1);
            mainMap.refresh();
            Minimap_update();*/
        }
        private Bitmap createSpriteAtlas()
        {
            int totalWidth = 0;
            int maxHeight = 0;

            foreach (frameInfo frame in frames)
            {
                totalWidth += frame.size.Width;
                maxHeight = frame.size.Height > maxHeight ? frame.size.Height : maxHeight;
            }

            Bitmap result = new Bitmap(totalWidth, maxHeight);
            Graphics g = Graphics.FromImage(result);
            totalWidth = 0;

            foreach (frameInfo frame in frames)
            {
                g.DrawImage(frame.sprite, new Point(totalWidth, 0));
                totalWidth += frame.size.Width;
            }

            return result;
        }
        private byte[] XMLCreate(Size atlasSize)
        {
            MemoryStream ms = new MemoryStream();
            //XmlTextWriter textWriter = new XmlTextWriter(@"animation.xml", Encoding.UTF8);
            XmlTextWriter textWriter = new XmlTextWriter(ms, Encoding.UTF8);

            textWriter.Formatting = Formatting.Indented;
            textWriter.WriteStartDocument();

            //                    <animation>
            //              	    <resource>
            //                 		    <frame count="2"/>
            //                          <sprite count="4"/>
            //                  		<atlas width="100" height="100"/>                  		
            //                  	</resource>
            //                  	<frame index="0" spriteIndex="0" X="0" Y="0" Width="10" Height="10" Rotate="100" Time="100">
            //                  	<frame index="1" spriteIndex="1" X="0" Y="0" Width="10" Height="10" Rotate="100" Time="100">
            //                    </animation>

            textWriter.WriteStartElement("animation");
            {
                textWriter.WriteStartElement("Info");
                {
                    textWriter.WriteStartElement("frame");
                    {
                        textWriter.WriteStartAttribute("count");
                        textWriter.WriteString(frames.Count.ToString());
                        textWriter.WriteEndAttribute();
                    }
                    textWriter.WriteEndElement();

                    textWriter.WriteStartElement("sprite");
                    {
                        textWriter.WriteStartAttribute("count");
                        textWriter.WriteString(sprites.Count.ToString());
                        textWriter.WriteEndAttribute();
                    }
                    textWriter.WriteEndElement();

                    textWriter.WriteStartElement("atlas");
                    {
                        textWriter.WriteStartAttribute("width");
                        textWriter.WriteString(atlasSize.Width.ToString());
                        textWriter.WriteEndAttribute();

                        textWriter.WriteStartAttribute("height");
                        textWriter.WriteString(atlasSize.Height.ToString());
                        textWriter.WriteEndAttribute();
                    }
                    textWriter.WriteEndElement();
                }
                textWriter.WriteEndElement();

                textWriter.WriteStartElement("resource");
                {
                    for (int i = 0; i < frames.Count; ++i)
                    {
                        textWriter.WriteStartElement("frame");
                        {
                            textWriter.WriteStartAttribute("index");
                            textWriter.WriteString(i.ToString());
                            textWriter.WriteEndAttribute();

                            textWriter.WriteStartAttribute("spriteIndex");
                            textWriter.WriteString(findSpriteIndex(frames[i].oriSprite).ToString());
                            textWriter.WriteEndAttribute();

                            textWriter.WriteStartAttribute("X");
                            textWriter.WriteString(frames[i].point.X.ToString());
                            textWriter.WriteEndAttribute();

                            textWriter.WriteStartAttribute("Y");
                            textWriter.WriteString(frames[i].point.Y.ToString());
                            textWriter.WriteEndAttribute();

                            textWriter.WriteStartAttribute("Width");
                            textWriter.WriteString(frames[i].sprite.Size.Width.ToString());
                            textWriter.WriteEndAttribute();

                            textWriter.WriteStartAttribute("Height");
                            textWriter.WriteString(frames[i].sprite.Size.Height.ToString());
                            textWriter.WriteEndAttribute();

                            textWriter.WriteStartAttribute("Rotate");
                            textWriter.WriteString(frames[i].rotate.ToString());
                            textWriter.WriteEndAttribute();

                            textWriter.WriteStartAttribute("Time");
                            textWriter.WriteString(frames[i].time.ToString());
                            textWriter.WriteEndAttribute();
                        }
                        textWriter.WriteEndElement();
                    }
                }
                textWriter.WriteEndElement();
            }
            textWriter.WriteEndElement();

            textWriter.WriteEndDocument();
            textWriter.Close();

            byte[] bytes = ms.ToArray();
            ms.Close();

            return bytes;
        }
        private void CSMCreate(string FileName)
        {
            MemoryStream ms = new MemoryStream();

            Bitmap atlas = createSpriteAtlas();
            atlas.Save(ms, System.Drawing.Imaging.ImageFormat.Png);
 
            using (ZipFile tmp = new ZipFile())
            {
                tmp.AddEntry("TEST.xml", "", XMLCreate(atlas.Size));
                tmp.AddEntry("atlas", "", ms.ToArray());

                for (int i = 0; i < originalSprites.Count; ++i)
                {
                    ms.Seek(0, SeekOrigin.Begin);
                    originalSprites[i].Save(ms, System.Drawing.Imaging.ImageFormat.Png);

                    tmp.AddEntry("sprite" + i.ToString(), "", ms.ToArray());
                }
                tmp.Save(FileName);
            }
        }
        private void saveButton_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog1 = new SaveFileDialog();

            saveFileDialog1.Filter = "Animation files|*.ani";
            saveFileDialog1.FilterIndex = 1;
            saveFileDialog1.RestoreDirectory = true;
            saveFileDialog1.InitialDirectory = System.IO.Directory.GetCurrentDirectory();

            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                CSMCreate(saveFileDialog1.FileName);
            }
        }
//         private void Frame_DoubleClick(object sender, EventArgs e)
//         {
//             if (frameImage != null)
//             {
//                 workSpace.Controls.Remove(frameImage);
//                 frameImage.Dispose();
//             }
// 
//             allocatedSprite = selectedSprite;
//             frameImage = new PictureBox();
// 
//             if (frames[selectedFrame].sprite != null)
//             {
//                 frameImage.Image = frames[selectedFrame].sprite;
//                 frameImage.Size = frames[selectedFrame].sprite.Size;
//                 frameImage.Location = new Point((workSpace.Size.Width - frames[selectedFrame].sprite.Size.Width) / 2, (workSpace.Size.Height - frames[selectedFrame].sprite.Size.Height) / 2);
//             }
// 
//             frameImage.MouseDown += new System.Windows.Forms.MouseEventHandler(this.workSpace_MouseDown);
//             frameImage.MouseMove += new System.Windows.Forms.MouseEventHandler(this.workSpace_MouseMove);
//             frameImage.MouseUp += new System.Windows.Forms.MouseEventHandler(this.workSpace_MouseUp);
// 
//             workSpace.Controls.Add(frameImage);
// 
//             updateTimeline();
//         }
    }
}
