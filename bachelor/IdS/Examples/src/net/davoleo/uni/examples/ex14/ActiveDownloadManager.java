package net.davoleo.uni.examples.ex14;

import net.davoleo.uni.aspects.Active;
import net.davoleo.uni.concurrent.Callback;
import net.davoleo.uni.concurrent.Future;
import net.davoleo.uni.examples.ex05.ResourceContent;

public interface ActiveDownloadManager extends Active<DownloadManager> {
	
	Future<ResourceContent> download(String url);
	
	void download(String url, Callback<ResourceContent> callback);

}
