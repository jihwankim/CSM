﻿namespace Maptool
{
    partial class main_map
    {
       
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        { 
            this.work_map = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.work_map)).BeginInit();
            this.SuspendLayout();
            // 
            // work_map
            // 
            this.work_map.Location = new System.Drawing.Point(0, 0);
            this.work_map.Name = "work_map";
            this.work_map.Size = new System.Drawing.Size(571, 404);
            this.work_map.TabIndex = 0;
            this.work_map.TabStop = false;
            this.work_map.MouseDown += new System.Windows.Forms.MouseEventHandler(this.main_map_MouseDown);
            this.work_map.MouseMove += new System.Windows.Forms.MouseEventHandler(this.GridCellHighlight);
            this.work_map.MouseUp += new System.Windows.Forms.MouseEventHandler(this.work_map_MouseUp);
            // 
            // main_map
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.ClientSize = new System.Drawing.Size(810, 620);
            this.ControlBox = false;
            this.Controls.Add(this.work_map);
            this.DoubleBuffered = true;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "main_map";
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.Text = "main_map";
            this.TopMost = true;
            this.Scroll += new System.Windows.Forms.ScrollEventHandler(this.main_map_Scroll);
            ((System.ComponentModel.ISupportInitialize)(this.work_map)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        public System.Windows.Forms.PictureBox work_map;
        



    }
}