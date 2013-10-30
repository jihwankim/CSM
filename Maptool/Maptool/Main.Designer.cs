﻿namespace Maptool
{
    partial class Main
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다.
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마십시오.
        /// </summary>
        private void InitializeComponent()
        {
            this.메뉴 = new System.Windows.Forms.MenuStrip();
            this.menu_file = new System.Windows.Forms.ToolStripMenuItem();
            this.menu_item_new = new System.Windows.Forms.ToolStripMenuItem();
            this.menu_item_open = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.menu_item_close = new System.Windows.Forms.ToolStripMenuItem();
            this.menu_item_close_all = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator6 = new System.Windows.Forms.ToolStripSeparator();
            this.menu_item_save = new System.Windows.Forms.ToolStripMenuItem();
            this.menu_item_save_as = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.menu_item_recent_file = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.menu_item_exit = new System.Windows.Forms.ToolStripMenuItem();
            this.menu_edit = new System.Windows.Forms.ToolStripMenuItem();
            this.menu_item_undo = new System.Windows.Forms.ToolStripMenuItem();
            this.menu_item_redo = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
            this.menu_item_cut = new System.Windows.Forms.ToolStripMenuItem();
            this.menu_item_copy = new System.Windows.Forms.ToolStripMenuItem();
            this.menu_item_paste = new System.Windows.Forms.ToolStripMenuItem();
            this.menu_item_delete = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator5 = new System.Windows.Forms.ToolStripSeparator();
            this.menu_item_select_all = new System.Windows.Forms.ToolStripMenuItem();
            this.menu_view = new System.Windows.Forms.ToolStripMenuItem();
            this.menu_tool = new System.Windows.Forms.ToolStripMenuItem();
            this.menu_help = new System.Windows.Forms.ToolStripMenuItem();
            this.menu_item_view_help = new System.Windows.Forms.ToolStripMenuItem();
            this.menu_item_report_a_bug = new System.Windows.Forms.ToolStripMenuItem();
            this.menu_item_info = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.label1 = new System.Windows.Forms.Label();
            this.메뉴.SuspendLayout();
            this.SuspendLayout();
            // 
            // 메뉴
            // 
            this.메뉴.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menu_file,
            this.menu_edit,
            this.menu_view,
            this.menu_tool,
            this.menu_help,
            this.toolStripMenuItem1});
            this.메뉴.Location = new System.Drawing.Point(0, 0);
            this.메뉴.Name = "메뉴";
            this.메뉴.Size = new System.Drawing.Size(765, 24);
            this.메뉴.TabIndex = 0;
            this.메뉴.Text = "menuStrip1";
            // 
            // menu_file
            // 
            this.menu_file.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menu_item_new,
            this.menu_item_open,
            this.toolStripSeparator3,
            this.menu_item_close,
            this.menu_item_close_all,
            this.toolStripSeparator6,
            this.menu_item_save,
            this.menu_item_save_as,
            this.toolStripSeparator2,
            this.menu_item_recent_file,
            this.toolStripSeparator1,
            this.menu_item_exit});
            this.menu_file.Name = "menu_file";
            this.menu_file.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.F)));
            this.menu_file.Size = new System.Drawing.Size(57, 20);
            this.menu_file.Text = "파일(F)";
            // 
            // menu_item_new
            // 
            this.menu_item_new.Name = "menu_item_new";
            this.menu_item_new.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.N)));
            this.menu_item_new.Size = new System.Drawing.Size(220, 22);
            this.menu_item_new.Text = "새로 만들기";
            // 
            // menu_item_open
            // 
            this.menu_item_open.Name = "menu_item_open";
            this.menu_item_open.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.menu_item_open.Size = new System.Drawing.Size(220, 22);
            this.menu_item_open.Text = "열기";
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(217, 6);
            // 
            // menu_item_close
            // 
            this.menu_item_close.Name = "menu_item_close";
            this.menu_item_close.Size = new System.Drawing.Size(220, 22);
            this.menu_item_close.Text = "닫기";
            // 
            // menu_item_close_all
            // 
            this.menu_item_close_all.Name = "menu_item_close_all";
            this.menu_item_close_all.Size = new System.Drawing.Size(220, 22);
            this.menu_item_close_all.Text = "모두 닫기";
            // 
            // toolStripSeparator6
            // 
            this.toolStripSeparator6.Name = "toolStripSeparator6";
            this.toolStripSeparator6.Size = new System.Drawing.Size(217, 6);
            // 
            // menu_item_save
            // 
            this.menu_item_save.Name = "menu_item_save";
            this.menu_item_save.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
            this.menu_item_save.Size = new System.Drawing.Size(220, 22);
            this.menu_item_save.Text = "저장";
            // 
            // menu_item_save_as
            // 
            this.menu_item_save_as.Name = "menu_item_save_as";
            this.menu_item_save_as.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.A)));
            this.menu_item_save_as.Size = new System.Drawing.Size(220, 22);
            this.menu_item_save_as.Text = "다른 이름으로 저장";
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(217, 6);
            // 
            // menu_item_recent_file
            // 
            this.menu_item_recent_file.Name = "menu_item_recent_file";
            this.menu_item_recent_file.Size = new System.Drawing.Size(220, 22);
            this.menu_item_recent_file.Text = "최근에 사용한 파일";
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(217, 6);
            // 
            // menu_item_exit
            // 
            this.menu_item_exit.Name = "menu_item_exit";
            this.menu_item_exit.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.F4)));
            this.menu_item_exit.Size = new System.Drawing.Size(220, 22);
            this.menu_item_exit.Text = "끝내기";
            this.menu_item_exit.Click += new System.EventHandler(this.menu_item_exit_MouseDown);
            this.menu_item_exit.Click += new System.EventHandler(this.menu_item_exit_MouseUp);
            // 
            // menu_edit
            // 
            this.menu_edit.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menu_item_undo,
            this.menu_item_redo,
            this.toolStripSeparator4,
            this.menu_item_cut,
            this.menu_item_copy,
            this.menu_item_paste,
            this.menu_item_delete,
            this.toolStripSeparator5,
            this.menu_item_select_all});
            this.menu_edit.Name = "menu_edit";
            this.menu_edit.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.E)));
            this.menu_edit.Size = new System.Drawing.Size(57, 20);
            this.menu_edit.Text = "편집(E)";
            // 
            // menu_item_undo
            // 
            this.menu_item_undo.Name = "menu_item_undo";
            this.menu_item_undo.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Z)));
            this.menu_item_undo.Size = new System.Drawing.Size(168, 22);
            this.menu_item_undo.Text = "실행 취소";
            // 
            // menu_item_redo
            // 
            this.menu_item_redo.Name = "menu_item_redo";
            this.menu_item_redo.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Y)));
            this.menu_item_redo.Size = new System.Drawing.Size(168, 22);
            this.menu_item_redo.Text = "다시 실행";
            // 
            // toolStripSeparator4
            // 
            this.toolStripSeparator4.Name = "toolStripSeparator4";
            this.toolStripSeparator4.Size = new System.Drawing.Size(165, 6);
            // 
            // menu_item_cut
            // 
            this.menu_item_cut.Name = "menu_item_cut";
            this.menu_item_cut.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.X)));
            this.menu_item_cut.Size = new System.Drawing.Size(168, 22);
            this.menu_item_cut.Text = "잘라내기";
            // 
            // menu_item_copy
            // 
            this.menu_item_copy.Name = "menu_item_copy";
            this.menu_item_copy.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.C)));
            this.menu_item_copy.Size = new System.Drawing.Size(168, 22);
            this.menu_item_copy.Text = "복사";
            // 
            // menu_item_paste
            // 
            this.menu_item_paste.Name = "menu_item_paste";
            this.menu_item_paste.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.V)));
            this.menu_item_paste.Size = new System.Drawing.Size(168, 22);
            this.menu_item_paste.Text = "붙여넣기";
            // 
            // menu_item_delete
            // 
            this.menu_item_delete.Name = "menu_item_delete";
            this.menu_item_delete.ShortcutKeys = System.Windows.Forms.Keys.Delete;
            this.menu_item_delete.Size = new System.Drawing.Size(168, 22);
            this.menu_item_delete.Text = "삭제";
            // 
            // toolStripSeparator5
            // 
            this.toolStripSeparator5.Name = "toolStripSeparator5";
            this.toolStripSeparator5.Size = new System.Drawing.Size(165, 6);
            // 
            // menu_item_select_all
            // 
            this.menu_item_select_all.Name = "menu_item_select_all";
            this.menu_item_select_all.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.A)));
            this.menu_item_select_all.Size = new System.Drawing.Size(168, 22);
            this.menu_item_select_all.Text = "모두 선택";
            // 
            // menu_view
            // 
            this.menu_view.Name = "menu_view";
            this.menu_view.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.V)));
            this.menu_view.Size = new System.Drawing.Size(59, 20);
            this.menu_view.Text = "보기(V)";
            // 
            // menu_tool
            // 
            this.menu_tool.Name = "menu_tool";
            this.menu_tool.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.T)));
            this.menu_tool.Size = new System.Drawing.Size(57, 20);
            this.menu_tool.Text = "도구(T)";
            // 
            // menu_help
            // 
            this.menu_help.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menu_item_view_help,
            this.menu_item_report_a_bug,
            this.menu_item_info});
            this.menu_help.Name = "menu_help";
            this.menu_help.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.H)));
            this.menu_help.Size = new System.Drawing.Size(72, 20);
            this.menu_help.Text = "도움말(H)";
            // 
            // menu_item_view_help
            // 
            this.menu_item_view_help.Name = "menu_item_view_help";
            this.menu_item_view_help.Size = new System.Drawing.Size(138, 22);
            this.menu_item_view_help.Text = "도움말 보기";
            // 
            // menu_item_report_a_bug
            // 
            this.menu_item_report_a_bug.Name = "menu_item_report_a_bug";
            this.menu_item_report_a_bug.Size = new System.Drawing.Size(138, 22);
            this.menu_item_report_a_bug.Text = "버그 보고";
            // 
            // menu_item_info
            // 
            this.menu_item_info.Name = "menu_item_info";
            this.menu_item_info.Size = new System.Drawing.Size(138, 22);
            this.menu_item_info.Text = "정보";
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(12, 20);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(335, 192);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(38, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "label1";
            // 
            // Main
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(765, 599);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.메뉴);
            this.MainMenuStrip = this.메뉴;
            this.Name = "Main";
            this.Text = "CSM Map Editor";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.메뉴.ResumeLayout(false);
            this.메뉴.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip 메뉴;
        private System.Windows.Forms.ToolStripMenuItem menu_file;
        private System.Windows.Forms.ToolStripMenuItem menu_item_new;
        private System.Windows.Forms.ToolStripMenuItem menu_item_open;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripMenuItem menu_item_save;
        private System.Windows.Forms.ToolStripMenuItem menu_item_save_as;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripMenuItem menu_item_recent_file;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem menu_item_exit;
        private System.Windows.Forms.ToolStripMenuItem menu_edit;
        private System.Windows.Forms.ToolStripMenuItem menu_item_undo;
        private System.Windows.Forms.ToolStripMenuItem menu_item_redo;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator4;
        private System.Windows.Forms.ToolStripMenuItem menu_item_cut;
        private System.Windows.Forms.ToolStripMenuItem menu_item_copy;
        private System.Windows.Forms.ToolStripMenuItem menu_item_paste;
        private System.Windows.Forms.ToolStripMenuItem menu_item_delete;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator5;
        private System.Windows.Forms.ToolStripMenuItem menu_item_select_all;
        private System.Windows.Forms.ToolStripMenuItem menu_view;
        private System.Windows.Forms.ToolStripMenuItem menu_tool;
        private System.Windows.Forms.ToolStripMenuItem menu_help;
        private System.Windows.Forms.ToolStripMenuItem menu_item_view_help;
        private System.Windows.Forms.ToolStripMenuItem menu_item_report_a_bug;
        private System.Windows.Forms.ToolStripMenuItem menu_item_info;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem menu_item_close;
        private System.Windows.Forms.ToolStripMenuItem menu_item_close_all;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator6;
        private System.Windows.Forms.Label label1;

    }
}

