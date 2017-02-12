#ifndef STORAGE_ACCESS_H
#define STORAGE_ACCESS_H

#include <memory>
#include <string>
#include <vector>

#include "utility/types.h"
#include "utility/file/FileInfo.h"
#include "utility/file/FilePath.h"

#include "data/bookmark/Bookmark.h"
#include "data/bookmark/BookmarkCategory.h"
#include "data/bookmark/EdgeBookmark.h"
#include "data/bookmark/NodeBookmark.h"
#include "data/parser/ParseLocation.h"
#include "data/graph/Node.h"
#include "data/search/SearchMatch.h"
#include "data/ErrorCountInfo.h"
#include "data/ErrorFilter.h"
#include "data/ErrorInfo.h"
#include "data/StorageStats.h"

class Graph;
class TextAccess;
class TokenLocation;
class TokenLocationCollection;
class TokenLocationFile;
class TimePoint;

class StorageAccess
{
public:
	virtual ~StorageAccess();

	virtual Id getIdForNodeWithNameHierarchy(const NameHierarchy& nameHierarchy) const = 0;
	virtual Id getIdForEdge(
		Edge::EdgeType type, const NameHierarchy& fromNameHierarchy, const NameHierarchy& toNameHierarchy) const = 0;
	virtual StorageEdge getEdgeById(Id edgeId) const = 0;

	virtual bool checkEdgeExists(Id edgeId) const = 0;

	virtual NameHierarchy getNameHierarchyForNodeWithId(Id id) const = 0;
	virtual Node::NodeType getNodeTypeForNodeWithId(Id id) const = 0;
	virtual bool checkNodeExistsByName(const std::string& serializedName) const = 0;

	virtual std::shared_ptr<TokenLocationCollection> getFullTextSearchLocations(
			const std::string& searchTerm, bool caseSensitive) const = 0;
	virtual std::vector<SearchMatch> getAutocompletionMatches(const std::string& query) const = 0;
	virtual std::vector<SearchMatch> getSearchMatchesForTokenIds(const std::vector<Id>& tokenIds) const = 0;

	virtual std::shared_ptr<Graph> getGraphForAll() const = 0;
	virtual std::shared_ptr<Graph> getGraphForActiveTokenIds(const std::vector<Id>& tokenIds, bool* isActiveNamespace = nullptr) const = 0;

	virtual std::vector<Id> getActiveTokenIdsForId(Id tokenId, Id* declarationId) const = 0;

	virtual std::vector<Id> getNodeIdsForLocationIds(const std::vector<Id>& locationIds) const = 0;
	virtual std::vector<Id> getLocalSymbolIdsForLocationIds(const std::vector<Id>& locationIds) const = 0;

	virtual std::vector<Id> getTokenIdsForMatches(const std::vector<SearchMatch>& matches) const = 0;
	virtual Id getTokenIdForFileNode(const FilePath& filePath) const = 0;

	virtual std::shared_ptr<TokenLocationCollection> getTokenLocationsForTokenIds(
			const std::vector<Id>& tokenIds) const = 0;
	virtual std::shared_ptr<TokenLocationCollection> getTokenLocationsForLocationIds(
			const std::vector<Id>& locationIds) const = 0;
	virtual std::shared_ptr<TokenLocationFile> getTokenLocationsForFile(const std::string& filePath) const = 0;
	virtual std::shared_ptr<TokenLocationFile> getTokenLocationsForLinesInFile(
		const std::string& filePath, uint firstLineNumber, uint lastLineNumber) const = 0;

	virtual std::shared_ptr<TokenLocationFile> getCommentLocationsInFile(const FilePath& filePath) const = 0;

	virtual std::shared_ptr<TextAccess> getFileContent(const FilePath& filePath) const = 0;

	virtual FileInfo getFileInfoForFilePath(const FilePath& filePath) const = 0;
	virtual std::vector<FileInfo> getFileInfosForFilePaths(const std::vector<FilePath>& filePaths) const = 0;

	virtual StorageStats getStorageStats() const = 0;

	virtual ErrorCountInfo getErrorCount() const = 0;
	virtual std::vector<ErrorInfo> getErrors() const = 0;

	virtual std::shared_ptr<TokenLocationCollection> getErrorTokenLocations(std::vector<ErrorInfo>* errors) const = 0;

	virtual void setErrorFilter(const ErrorFilter& filter);

	virtual Id addNodeBookmark(const NodeBookmark& bookmark) = 0;
	virtual Id addEdgeBookmark(const EdgeBookmark& bookmark) = 0;
	virtual Id addBookmarkCategory(const BookmarkCategory& category) = 0;

	virtual std::vector<NodeBookmark> getAllNodeBookmarks() const = 0;
	virtual NodeBookmark getNodeBookmarkById(const Id bookmarkId) const = 0;
	virtual bool checkNodeBookmarkExistsByTokens(const std::vector<std::string>& tokenNames) const = 0;
	virtual void removeNodeBookmark(Id id) = 0;
	virtual void editNodeBookmark(const NodeBookmark& bookmark) = 0;

	virtual std::vector<EdgeBookmark> getAllEdgeBookmarks() const = 0;
	virtual EdgeBookmark getEdgeBookmarkById(const Id bookmarkId) const = 0;
	virtual bool checkEdgeBookmarkExistsByTokens(const std::vector<std::string>& tokenNames) const = 0;
	virtual void removeEdgeBookmark(Id id) = 0;
	virtual void editEdgeBookmark(const EdgeBookmark& bookmark) = 0;

	virtual std::vector<BookmarkCategory> getAllBookmarkCategories() const = 0;
	virtual bool checkBookmarkCategoryExists(const std::string& name) const = 0;
	virtual void removeBookmarkCategory(Id id) = 0;

protected:
	ErrorFilter m_errorFilter;
};

#endif // STORAGE_ACCESS_H
